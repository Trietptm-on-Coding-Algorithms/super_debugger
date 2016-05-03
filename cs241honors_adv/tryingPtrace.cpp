/**
 * 	@file: pTrace
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 *	NO WARRANTY
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

using namespace std;

// struct for registers
struct user_regs_struct regs;


// can only do watchpoints for main currently
// sed -i -e 's/cout/cerr/g' tryingPtrace.cpp to replace cout with cerr

// --------------- WATCHPOINTS --------------------


// stores the watch variable data --- only non char* for now, cannot change char* anyways
struct watchpt_info {
	long data;			
	int type;
	int times_hit;			// first time hit, we give them warning message about garbage
};

// map to store all info about watchpoints
map< string, map<string, watchpt_info> > all_watchpts;				// function -> variable name, watchpoint info

// used for inserting batches of watchpoints --- insert into curr_function
set< string > watchpt_batch;

// map to store index of watchpoint --- almost useless
map< string, map<string, int> > helper_watchpt;		// function -> variable name, watchpoint number
map< string, map<int, string> > watchpt_idx;				// function -> watchpoint number, variable name

// the number of watchpoints
int watchpt_num;


// --------------- BREAKPOINTS --------------------


// stores the breakpoint instruction data so we can restore it later 
struct brkpt_info {
  long former_data;
  void* orig_addr;
  void* brkpt_addr;				// 1 more than original
  int times_hit;				// can use this if we want to
};

// map to store all info about breakpoints
// stores actual instruction address
map< void*, brkpt_info > all_brkpts;				// address, breakpoint info

// abstraction for real breakpoint
// memory address to breakpoint number --- almost useless
map< void*, int > helper_brkpt;				// address, breakpoint number
map< int, void* > brkpt_idx;				// breakpoint number, address

// used for inserting batches of breakpoints
set< void* > brkpt_batch;

// the number of breakpoints
int brkpt_num;

// used for resetting the breakpoint
bool reset_brkpt;
brkpt_info former_brkpt;
bool cont_flag; 

// stores the former line number for stepping
int former_line;

// stores former line for watch point
int watch_line;

// used to check if we stepped or watchpointed
bool step_flag;

// --------------- GENERAL --------------------

// the current function we are at
string curr_function;


/**
 *	All valid input commands for our pTrace-debugger
 *
 */
static string cont_cmds[] = {"c", "continue"};
static string next_cmds[] = {"n", "next", "s", "step"};
static string exit_cmds[] = {"kill", "quit", "q", "exit"};

static string reg_cmds[] = {"reg", "regs", "registers"};
static string help_cmds[] = {"help"};

static string run_cmds[] = {"run", "r"};

static string break_cmds[] = {"break", "br", "b", "brk"};
static string rm_brk_cmds[] = {"clear", "rm", "remove", "d", "delete"};
static string watch_cmds[] = {"watch", "w"};
static string rm_watch_cmds[] = {"clearw", "rmw", "dw"};

static string info_brk_cmds[] = {"info", "i"};
static string print_cmds[] = {"print", "p"};

// forward declarations for now
void switch_symbol_table( pid_t pid, int line_num );


/**
 *	Gets the instruction pointer
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return The address of the instruction pointer
 */
void* get_instr_ptr( pid_t pid ) {
	return (void*)ptrace( PTRACE_PEEKUSER, pid, 8 * RIP, NULL );
}


/**
 *	Sets the instruction pointer
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void set_instr_ptr( pid_t pid, void* addr ) {
	ptrace( PTRACE_POKEUSER, pid, 8 * RIP, addr );
}


/**
 *	Gets the base pointer
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return The address of the stack pointer
 */
void* get_base_ptr( pid_t pid ) {
	return (void*)ptrace( PTRACE_PEEKUSER, pid, 8 * RBP, NULL );
}


/**
 *	Gets the instruction pointer
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return The address of the stack pointer
 */
void* get_stack_ptr( pid_t pid ) {
	return (void*)ptrace( PTRACE_PEEKUSER, pid, 8 * RSP, NULL );
}


/**
 *	Gets the return address
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param stack_pointer: The (current) stack pointer
 * 	@return The return address of a function
 */
void* get_ret_addr( pid_t pid, void* stack_pointer ) {
	return (void*)ptrace( PTRACE_PEEKTEXT, pid, stack_pointer, NULL );
}


/**
 *	Gets the data from the specified address
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param addr: The address of the data we want to access
 * 	@return The data at the specified address 
 */
long get_data( pid_t pid, void* addr ) {
	return ptrace( PTRACE_PEEKDATA, pid, addr, NULL );
}


/**
 *	Sets the data at the specified address
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param addr: The address of the data we want to access
 * 	@param data: The data we want to set at the specified address
 */
void set_data( pid_t pid, void* addr, void* data ) {
	ptrace( PTRACE_POKEDATA, pid, addr, data );
}


/**
 *	Gets all the register values and stores it in the struct 'regs' defined globally above
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void getRegisters( pid_t pid ) {
	ptrace( PTRACE_GETREGS, pid, NULL, &regs );
}


/**
 *	Prints all the registers which gdb prints
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void printRegisters( pid_t pid ) {
	cerr << "\n";
	cerr << "Register rax:\t\t" << ( void* )regs.rax << "\n";
	cerr << "Register rbx:\t\t" << ( void* )regs.rbx << "\n";
	cerr << "Register rcx:\t\t" << ( void* )regs.rcx << "\n";
	cerr << "Register rdx:\t\t" << ( void* )regs.rdx << "\n";
	cerr << "Register rsi:\t\t" << ( void* )regs.rsi << "\n";
	cerr << "Register rdi:\t\t" << ( void* )regs.rdi << "\n";
	cerr << "Register rbp:\t\t" << ( void* )regs.rbp << "\n";
	cerr << "Register rsp:\t\t" << ( void* )regs.rsp << "\n";
	cerr << "Register r8:\t\t" << ( void* )regs.r8 << "\n";
	cerr << "Register r9:\t\t" << ( void* )regs.r9 << "\n";
	cerr << "Register r10:\t\t" << ( void* )regs.r10 << "\n";
	cerr << "Register r11:\t\t" << ( void* )regs.r11 << "\n";
	cerr << "Register r12:\t\t" << ( void* )regs.r12 << "\n";
	cerr << "Register r13:\t\t" << ( void* )regs.r13 << "\n";
	cerr << "Register r14:\t\t" << ( void* )regs.r14 << "\n";
	cerr << "Register r15:\t\t" << ( void* )regs.r15 << "\n";
	cerr << "Register rip:\t\t" << ( void* )regs.rip << "\n";
	cerr << "Register eflags:\t" << ( void* )regs.eflags << "\n";
	cerr << "Register cs:\t\t" << ( void* )regs.cs << "\n";
	cerr << "Register ss:\t\t" << ( void* )regs.ss << "\n";
	cerr << "Register ds:\t\t" << ( void* )regs.ds << "\n";
	cerr << "Register es:\t\t" << ( void* )regs.es << "\n";
	cerr << "Register fs:\t\t" << ( void* )regs.fs << "\n";
	cerr << "Register gs:\t\t" << ( void* )regs.gs << "\n\n";
}


/**
 *	Prints the intro for our pTrace-debugger
 *
 */
void printIntro() {
	cerr << "\e[1m\n *** Welcome to sdb ***\n\n";
	cerr << "Start / Run your program with 'r' or 'run'\n";
	cerr << "Set breakpoints with 'break', 'br', or 'b' along with the line number or function\n";
	cerr << "Delete breakpoints with 'clear', 'rm', 'remove', 'd', or 'delete'\n\t";
	cerr << "\talong with the line number or function name\n";
	cerr << "Set watchpoints with 'watch' or 'w' along with the variable name\n";
	cerr << "Delete watchpoints with 'clearw', 'rmw', or 'dw' along with the variable name\n";
	cerr << "Look up your active break/watch points with 'i' or 'info'\n";
	cerr << "Continue your program with 'c' or 'continue'\n";
	cerr << "Step through your program line by line with 'n', 'next', 's', or 'step'\n";
	cerr << "Stop debugging your program with 'kill', 'q', 'quit', or 'exit'\n";
	cerr << "Print variable values with 'print' or 'p' along with the variable name\n";
	cerr << "\tprint value may be garbage if variable is not currently in scope\n";
	cerr << "Print values of common registers with 'reg', 'regs', or 'registers'\n";
	cerr << "For more advanced features type 'help' to get the complete functionality of sdb\e[0m\n\n"; 
}


/**
 *	Prints out information
 *
 */
void printHelp() {
	
}


/**
 *	Create a breakpoint at the address specified
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param addr: The address of the data we want to set a breapoint at
 * 	@param is_new_brkpt: Whether this breakpoint is a new breakpoint or not
 */
void set_brkpt( pid_t pid, void* addr, bool is_new_brkpt ) {			
	// need to check if breakpoint is already set or not --- do not want duplicates
	if ( is_new_brkpt ) {
		if ( all_brkpts.find(addr) != all_brkpts.end() )	{			// duplicate breakpoint
			cerr << "Breakpoint already set at this address, breakpoint request ignored\n";
			return;
		}
	}
				
	// inject INT 3 = 0xCC --- this is an interrupt, sends signal to debugger
	long new_data = get_data( pid, addr );
	long former_data = new_data;
	new_data = ( new_data & ~0xFF ) | 0xCC;
	set_data( pid, addr, (void*)new_data );

	// if it is a new breakpoint, we need to add it
	if ( is_new_brkpt ) {
		// need to store the former instruction pointer and data
		brkpt_info storage;
		storage.former_data = former_data;
		storage.orig_addr = addr;
		storage.brkpt_addr = addr + 1;			// instr addr will be one past due to INT3 opcode 
		all_brkpts[addr] = storage;					// add in map
	}
}


/**
 *	Create a watchpoint for the symbol (variable) specified
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param symbol: The variable we want to watch 
 */
void set_watchpt( pid_t pid , string symbol ) {
	map< string, symbol_data >& symbol_table = all_functs[curr_function].symbol_table;
	symbol_data sym = symbol_table[symbol];
	
	watchpt_info storage;
	long data = get_data( pid, (void*)sym.addr );
	storage.data = data;
	storage.type = sym.type;
	storage.times_hit = 0;
	all_watchpts[curr_function][symbol] = storage;
}


/**
 *	Checks if a watchpoint exist or not
 *
 * 	@return True if a watchpoint exists
 */
bool watchpt_exist() {
	for ( auto it = all_watchpts.begin(); it != all_watchpts.end(); ++it ) {
		if ( (it -> second).size() )
			return true;
	}
	
	return false;
}


/**
 *	Sets the data and instruction pointer back to its pre-breakpoint state
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param instr_ptr: The former instruction pointer address
 * 	@param data: The data the former instruction pointer was referencing
 */
void handle_brkpt( pid_t pid, void* instr_ptr, void* data ) {
	set_data( pid, instr_ptr, data );
	set_instr_ptr( pid, instr_ptr );
}


/**
 *	Check to see if the current instruction is a breakpoint
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return True if we are at a breakpoint
 */
bool is_brkpt( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( all_brkpts.find(instr_addr - 1) != all_brkpts.end() )		
		return true;
	
	return false;
}


/**
 *	Check to see if we singlestepped to a breakpoint instruction
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return True if we are at a breakpoint
 */
bool is_brkpt_step( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( all_brkpts.find(instr_addr) != all_brkpts.end() )		
		return true;
	
	return false;
}


/**
 *	Gets the line number of the current process
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return The line number of the current process
 */
int get_linenum( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );
	return addr_to_line[instr_addr];
}


/**
 *	Converts paramter string to lowercase 
 *
 * 	@param str: The command we want to lowercase
 */
void str_to_lower( string &str ) {
	transform( str.begin(), str.end(), str.begin(), ::tolower);
}


/**
 *	Checks whether the input is a valid line number
 *
 * 	@param input: A string of characters to check whether it is a valid number 
 * 	@return True if the input is a valid number
 */
bool is_num( string &input ) {
	// only checking line number
	for ( int i = 1; i < input.length(); ++i ) {
		if ( !isdigit(input[i]) ) {
			cerr << "Break input: '" << input << "' is undefined\n";
			return false;
		}
	}
	
	return true;
}


/**
 *	Checks whether the input is a valid function  
 *
 * 	@param input: A string of characters to check whether it is a valid function
 * 	@return True if the input is a valid function
 */
bool is_valid_func( string &input ) {
	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {
		if ( !input.compare(it -> first) )
			return true;
	}
	
	cerr << "Function name: '" << input << "' is undefined\n";
	return false;
}


/**
 *	Checks whether the command provided is a 'next' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'next' command was provided
 */
bool input_next( string &input ) {	
	for ( int i = 0; i < 4; ++i )
		if ( !input.compare(next_cmds[i]) )
			return true;
			
	return false;
}


/**
 *	Checks whether the command provided is a 'break' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'break' command was provided
 */
bool input_break( string &input ) {
	if ( !input.find("break ") || !input.find("br ") || !input.find("b ") || !input.find("brk ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'print' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'print' command was provided
 */
bool input_print( string &input ) {
	if ( !input.find("print ") || !input.find("p ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'remove watch' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'remove watch' command was provided
 */
bool input_rm_watch( string &input ) {
	if ( !input.find("rmw ") || !input.find("clearw ") || !input.find("dw ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'remove' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'remove' command was provided
 */
bool input_rm( string &input ) {
	if ( !input.find("rm ") || !input.find("remove ") || !input.find("clear ") || !input.find("d ") || !input.find("delete ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'watch' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'watch' command was provided
 */
bool input_watch( string &input ) {
	if ( !input.find("watch ") || !input.find("w ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'exit' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'exit' command was provided
 */
bool input_exit( string &input ) {
	for ( int i = 0; i < 4; ++i )
		if ( !input.compare(exit_cmds[i]) )
			return true;

	return false;
} 


/**
 *	Confirmation function to request if the user wants to exit
 *
 * 	@return True if the user wants to exit
 */
bool confirm_exit() {
	string str;

	while ( 1 ) {
		cerr << "Are you sure you want to quit? ('y'/'yes' or 'n'/'no') ";
		getline( cin, str );
		
		// lowercase in case
		str_to_lower( str );
		
		if ( !str.compare("y") || !str.compare("yes") ) {				// if yes
			return true;
		}
		else if ( !str.compare("n") || !str.compare("no") ) {		// if no
			return false;
		}
		else {
			cerr << "Invalid answer: '" << str << "'\n";
		}
	}
	
	return false;
}


/**
 *	Initial helper to insert the breakpoint
 *
 * 	@param addr: The address of the line
 * 	@param line_num: The line number we want to insert into
 * 	@param direct_hit: If we asked for a correct line number
 */
void insert_brkpt_helper( void* addr, int line_num, bool direct_hit ) {
	if ( end_of_function(line_num) ) {
		cerr << "Cannot set breakpoint at the end of a function, consider the line above\n"; 
		return;
	}
	
	++brkpt_num;
	
	// insert breakpoints into abstraction structures
	helper_brkpt[ addr ] = brkpt_num;
	brkpt_idx[ brkpt_num ] = addr;
	brkpt_batch.insert( addr );
	
	if ( !direct_hit ) 
		cerr << "Was not able to find line number, inserting at next available point instead\n";
	
	cerr << "Breakpoint " << brkpt_num << " set at address: '" << addr << "', file: '";
	cerr << filename << "', line: '" << line_num << "'\n";
}


/**
 *	Finds the breakpoint location, used for setting breakpoints (cannot set directly at main)
 *
 * 	@param str: The line number / function name encoded in a string
 * 	@param is_line_num: Whether the breakpoint is at a line number of function
 */
void find_print_brk_loc( string &str, bool is_line_num ) {
	if ( is_line_num ) {
		int line_num = 2147483647;
		if ( str.length() <= 9 ) 
			line_num = stoi( str );
			
		auto it = line_to_addr.begin();
		
		// if we can find the address of the line (it corresponds to a line number in the source file)
		if ( (it = line_to_addr.find(line_num)) != line_to_addr.end() && !is_funct_start(line_num) ) {
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) 
				insert_brkpt_helper( it -> second, line_num, true );
			else cerr << "Breakpoint already set at this address, breakpoint request ignored\n";
		}
		else if ( (it = line_to_addr.lower_bound(line_num)) != line_to_addr.end() ) {	
			if ( is_funct_start(it -> first) )
				++it;
				
			assert( (it != line_to_addr.end()) && "Something went wrong, debugger terminating" ); 
				
			// if we do not match any of the line numbers, we put it at the first line after the requested line
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) 
				insert_brkpt_helper( it -> second, addr_to_line[ it -> second ], false );
			else cerr << "Breakpoint already set at a later address, breakpoint request ignored\n";
		}
		else {
			cerr << "Line number is past end of file, breakpoint not set\n";
		}
	}
	else {
		// is function name
		int line_num = all_functs[str].start_line;			// get the line number
		auto it = line_to_addr.begin();
		
		assert( ((it = line_to_addr.find(line_num)) != line_to_addr.end()) && "Something went wrong, debugger terminating" ); 
		++it;
		assert( (it != line_to_addr.end()) && "Something went wrong, debugger terminating" ); 
		
		if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) 
			insert_brkpt_helper( it -> second, it -> first, true );
		else cerr << "Breakpoint already set at this address, breakpoint request ignored\n";
	}
}


/**
 *	Initial helper to remove the breakpoint
 *
 * 	@param pid: Process ID of the child (debuggee)  
 * 	@param line_num: The line number we want to insert into
 */
void rm_brkpt_helper( pid_t pid, int line_num ) {
	assert( (line_num != -1) && "Something went wrong, debugger terminating" ); 

	auto line_it = line_to_addr.begin();			// line_it -> second = address
	
	// if we find the line number
	if ( (line_it = line_to_addr.find(line_num)) != line_to_addr.end() ) {
		auto it = helper_brkpt.begin();	
		// if there is a breakpoint at the line number
		if ( (it = helper_brkpt.find(line_it -> second)) != helper_brkpt.end() ) {
			cerr << "Removing breakpoint at line: '" << line_num << "'\n";
			brkpt_idx.erase( it -> second );				// delete
			helper_brkpt.erase( it );				
			brkpt_batch.erase( line_it -> second );
			
			auto all_brkpts_it = all_brkpts.begin();
			
			// breakpoint is currently set --- need to go in and recover former data
			if ( (all_brkpts_it = all_brkpts.find( line_it -> second )) != all_brkpts.end() ) {
				brkpt_info temp = all_brkpts_it -> second;
				
				// resets the data back to normal --- do NOT reset the instruction pointer
				set_data( pid, temp.orig_addr, (void*)temp.former_data );

				void* instr_addr = get_instr_ptr( pid );
				
				// check if we are currently stopped at this breakpoint we want to remove
				if ( instr_addr == line_it -> second ) 
					reset_brkpt = false;
				
				all_brkpts.erase( all_brkpts_it );			// delete it at the end
			}		
		}
		else {
			cerr << "Breakpoint was never set at line: '" << line_num << "'\n";
		}
	}
	else {
		cerr << "Breakpoint was never set at line: '" << line_num << "'\n";
	}
}


/**
 *	Find and remove breakpoint
 *
 * 	@param pid: Process ID of the child (debuggee)  
 * 	@param str: The line number / function name encoded in a string
 * 	@param is_line_num: Whether the breakpoint is at a line number of function
 */
void find_print_rm_loc( pid_t pid, string &str, bool is_line_num ) {
	int line_num = -1;
	
	if ( is_line_num ) {
		if ( str.length() <= 9 ) 
			line_num = stoi( str );
		else line_num = 2147483647;	
	}
	else {			// is function
		line_num = all_functs[str].start_line;		
		auto it = line_to_addr.begin();
		
		assert( ((it = line_to_addr.find(line_num)) != line_to_addr.end()) && "Something went wrong, debugger terminating" ); 
		++it;
		assert( (it != line_to_addr.end()) && "Something went wrong, debugger terminating" ); 
		
		line_num = it -> first;
	}	
	
	rm_brkpt_helper( pid, line_num );
}


/**
 *	Handler for setting or removing breakpoints
 *
 * 	@param pid: Process ID of the child (debuggee)  
 * 	@param input_cmd: The line number / function name encoded in a string
 * 	@param in_break: Whether we are inserting a breakpoint or not, true = inserting
 */
void handle_brk_or_rm( pid_t pid, string input_cmd, bool in_break /* true: is setting brkpt */ ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	
	if ( (input_cmd[0] == '-') ) {
		if ( in_break )
			cerr << "Line number is not valid, breakpoint not set\n";
		else cerr << "Line number is not valid\n";
	}
	else if ( isdigit(input_cmd[0]) ) {					// check if it is a number
		if ( is_num(input_cmd) ) { 
			if ( in_break )
				find_print_brk_loc( input_cmd, true );					// breakpoint print out handler
			else find_print_rm_loc( pid, input_cmd, true );	
		}
	}
	else {
		if ( is_valid_func(input_cmd) ) {					// check if it is a function
			if ( in_break )
				find_print_brk_loc( input_cmd, false );
			else find_print_rm_loc( pid, input_cmd, false );	
		}
	}
}


/**
 *	Handler for removing watchpoints
 *
 * 	@param pid: Process ID of the child (debuggee)  
 * 	@param input_cmd: The variable name encoded in a string
 */
void handle_rm_watch(  pid_t pid, string input_cmd ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	map< string, symbol_data >& symbol_table = all_functs[curr_function].symbol_table;
	
	auto it = all_watchpts[curr_function].begin();
	auto batch_it = watchpt_batch.begin();
	
	if ( (it = all_watchpts[curr_function].find(input_cmd)) != all_watchpts[curr_function].end() ) {
		all_watchpts[curr_function].erase(it);
		int idx = helper_watchpt[curr_function][input_cmd];
		helper_watchpt[curr_function].erase( input_cmd );
		watchpt_idx[curr_function].erase( idx );
		cerr << "Removing watchpoint " << idx << ": '" << input_cmd << "'\n";
	}
	else if ( (batch_it = watchpt_batch.find(input_cmd)) != watchpt_batch.end() ) {
		watchpt_batch.erase(input_cmd);
		int idx = helper_watchpt[curr_function][input_cmd];
		helper_watchpt[curr_function].erase( input_cmd );
		watchpt_idx[curr_function].erase( idx );
		cerr << "Removing watchpoint " << idx << ": '" << input_cmd << "'\n";
	}
	else if ( symbol_table.find(input_cmd) != symbol_table.end() ) {					// check if valid variable name
		cerr << "Watchpoint was never set at '" << input_cmd << "'\n";
	}
	else {
		cerr << "Cannot find variable: '" << input_cmd << "'\n";
	}	
}


/**
 *	Prints out all break/watch point infomation, called when user inputs 'info' command
 *
 */
void print_allpt_info() {
	if ( !brkpt_idx.size() ) {
		cerr << "No active breakpoints are set\n\n";
	}
	else {
		cerr << "  Number\tType\t\tAddress\t\tLocation\n";
		
		for ( auto it = brkpt_idx.begin(); it != brkpt_idx.end(); ++it ) {
			int line_num = addr_to_line[ it -> second ];
			cerr << "    " << it -> first << "\t     breakpoint\t\t" << it -> second << "\t" << get_function( line_num );
			cerr << "() at " << filename << ":" << line_num << "\n";
		}
		
		cerr << "\n";
	}
	
	if ( !watchpt_idx.size() ) {
		cerr << "No active watchpoints are set\n\n";
	}
	else {
		cerr << "  Number\tType\t\tName\t\tFunction\n";
		for ( auto out_it = watchpt_idx.begin(); out_it != watchpt_idx.end(); ++out_it ) {
			for ( auto it = watchpt_idx[out_it -> first].begin(); it != watchpt_idx[out_it -> first].end(); ++it ) 
				cerr << "    " << it -> first << "\t     watchpoint\t\t" << it -> second << "\t\t" << out_it -> first << "()\n";
		}
		
		cerr << "\n";	
	}
}


/**
 *	Inserts all the watchpoints, called after user provided 'continue' command
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void insert_watchpt_batch( pid_t pid ) {
	for ( auto it = watchpt_batch.begin(); it != watchpt_batch.end(); ) {
		set_watchpt( pid, *it );
		watchpt_batch.erase( it++ /* makes a copy and destroys current iterator */ );
	}
}


/**
 *	Inserts all the breakpoints, called after user provided 'continue' command
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void insert_brkpt_batch( pid_t pid ) {
	for ( auto it = brkpt_batch.begin(); it != brkpt_batch.end(); ) {
		set_brkpt( pid, *it, true );
		brkpt_batch.erase( it++ /* makes a copy and destroys current iterator */ );
	}
}


/**
 *	Helper to handle breakpoints
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param in_step: Whether we are stepping through our breakpoint
 */
void brkpt_handler( pid_t pid, bool in_step ) {
	void* instr_addr = get_instr_ptr( pid );
	void* new_instr_addr = instr_addr;

	// since we are 1 past due to INT 3, we need to decrement
	if ( !in_step )
		new_instr_addr = instr_addr - 1;

	int line_num = addr_to_line[new_instr_addr];	
	
	// check to see if we should switch out the symbol table
	switch_symbol_table( pid, line_num );
				
	cerr << "\nBreakpoint " << helper_brkpt[new_instr_addr] << ", " << curr_function << "() at " << filename << ":" << line_num << "\n";
	cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";		

	// need to handle breakpoint
	brkpt_info curr_brkpt = all_brkpts[new_instr_addr];
	handle_brkpt( pid, curr_brkpt.orig_addr, (void*)curr_brkpt.former_data );	
	
	// indicate we need to reset this breakpoint
	reset_brkpt = true;
	former_brkpt = curr_brkpt;
}


/**
 *	Subtract the base pointer from the symbol table to get back the offsets
 * 
 * 	@param pid: Process ID of the child (debuggee)
 * 	@param function: The function corresponding to the symbol table  
 */
void delete_symbols( pid_t pid, string function ) {
	void* base_ptr = all_functs[function].base_ptr_addr;
	map< string, symbol_data >& symbol_table = all_functs[function].symbol_table;
	
	for ( auto it = symbol_table.begin(); it != symbol_table.end(); ++it ) 
		(it -> second).addr -= (long)base_ptr;
		
	all_functs[function].symbol_filled = false;	
}


/**
 *	Fills the symbol table with our symbols (parsed from objdump)
 * 
 * 	@param pid: Process ID of the child (debuggee)
 * 	@param function: The function corresponding to the symbol table  
 */
void fill_symbols( pid_t pid, string function ) {
	void* base_ptr = get_base_ptr( pid );	
	all_functs[function].base_ptr_addr = base_ptr;
	map< string, symbol_data >& symbol_table = all_functs[function].symbol_table;
	
	for ( auto it = symbol_table.begin(); it != symbol_table.end(); ++it ) 
		(it -> second).addr += (long)base_ptr;
		
	all_functs[function].symbol_filled = true;	
}


/**
 *	Builds the symbol table - called after initial stop
 *
 * 	@param pid: Process ID of the child (debuggee)
 * 	@param function: The function corresponding to the symbol table 
 */
void build_symbol_table( pid_t pid, string function ) {
	// get and fill all the symbols from the base pointer
	fill_symbols( pid, function );
	insert_watchpt_batch( pid );	
	
	if ( all_watchpts[curr_function].size() )				// we have active watchpoints --- need to singlestep
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
	else ptrace( PTRACE_CONT, pid, NULL, NULL );
}


/**
 *	Helper to switch out the current symbol table (if we do)
 *
 * 	@param pid: Process ID of the child (debuggee)
 * 	@param line_num: The current line number we want to check
 */
void switch_symbol_table( pid_t pid, int line_num ) {
	string function = get_function( line_num );
	
	assert( function.compare("-invalid-") && "Line number does not correspond to a function" );

	// might have errors --- hacky fix below
	// need to also check if it is not the beginning of a function since the base pointer haven't updated yet
	if ( function.compare(curr_function) && !is_funct_start(line_num) ) {					// if not the same as current function		
		// subtract the base pointer so we get the offsets again --- also need to move them
		delete_symbols( pid, curr_function );
	
		curr_function = function;

		// build the symbol table if it was not built already
		if ( !all_functs[curr_function].symbol_filled ) 
			fill_symbols( pid, curr_function );	
	}
}


/**
 *	Finds the location of main and sets a breakpoint there
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void set_brkpt_main( pid_t pid ) {
	set_brkpt( pid, all_functs["main"].get_base_addr, true );	
}


/**
 *	Prints the string pointed to by the char pointer
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param text_addr: The address the char pointer is pointing to
 */
void print_char_sym( pid_t pid, long text_addr ) {
	char c[8];
	long char_arr;
	bool flag = true;
	int idx = 0;
	vector< char > str;
	
	do {
		char_arr = get_data( pid, (void*)(text_addr + idx) );
		memcpy( c, &char_arr, 8 );
		for ( int i = 0; i < 8; ++i ) {
			if ( c[i] == 0 ) {
				flag = false;
				break;
			}
			else {
				str.push_back( c[i] );
			}
		}
		
		idx += 8;
	
	} while ( flag && idx < 1024 /* arbitrary bound */ );
	
	if ( idx == 1024 ) {				// is this necessary?
		cerr << "String is too big (over 1024 bytes) - make sure to null terminate\n";
	}
	else {
		int str_size = str.size();
		
		cerr << "\"";
		for ( int i = 0; i < str_size; ++i )
			cerr << str[i];
		cerr << "\"\n";
	}
}


/**
 *	Print the data represented as the passed in type
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param data: The data we want to print
 * 	@param type_idx: The integer corresponding to a type in the type array
 */
void print_types( pid_t pid, long data, int type_idx ) {
	assert( (type_idx >= 0 && type_idx <= 13) && "Something went wrong, debugger terminating" ); 

	if ( type_idx == 0 ) {
		cerr << (unsigned int)data << "\n";
	}
	else if ( type_idx == 1 ) {
		cerr << (unsigned long long)data << "\n";
	}
	else if ( type_idx == 2 ) {
		cerr << (unsigned long)data << "\n";
	}
	else if ( type_idx == 3 ) {
		cerr << (long long)data << "\n";
	}
	else if ( type_idx == 4 ) {		
		cerr << (int)data << "\n";
	}
	else if ( type_idx == 5 ) {			// long
		cerr << data << "\n";
	}
	else if ( type_idx == 6 ) {
		// convert to double
		long double data_double;
		memcpy( &data_double, &data, sizeof(long double) );
		cerr << setprecision( 10 ) << data_double << "\n";
	}
	else if ( type_idx == 7 ) {
		// convert to double
		double data_double;
		memcpy( &data_double, &data, sizeof(double) );
		cerr << setprecision( 10 ) << data_double << "\n";
	}
	else if ( type_idx == 8 ) {
		// convert to float
		float data_float;
		memcpy( &data_float, &data, sizeof(float) );
		cerr << setprecision( 7 ) << data_float << "\n";
	}
	else if ( type_idx == 9 ) {
		cerr << (unsigned short)data << "\n";
	}
	else if ( type_idx == 10 ) {
		cerr << (short)data << "\n";
	}
	else if ( type_idx == 11 ) {
		cerr << "'" << (char)data << "'\n";
	}
	else if ( type_idx == 12 ) {
		// since char* is in text segment, we get back an address (data)
		print_char_sym( pid, data );
	}
	else {				// type == 13
		// cannot do strings currently
		
	}
}


/**
 *	Print the symbol (variable name) value which is passed in, should be in scope
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param symbol: The symbol that we want to print
 */
void print_symbol( pid_t pid, string &symbol ) {
	map< string, symbol_data >& symbol_table = all_functs[curr_function].symbol_table;
	
	auto it = symbol_table.begin();
	if ( (it = symbol_table.find(symbol)) != symbol_table.end() ) {
		symbol_data sym = it -> second;
		long data = get_data( pid, (void*)sym.addr );
		
		// manual printing --- NOT portable
		print_types( pid, data, sym.type );
	}
	else {		
		cerr << "Cannot find variable: '" << symbol << "'\n";
	}
}


/**
 *	Handler for when the user provides the 'print' command
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param input_cmd: The symbol that we want to print
 */
void handle_print( pid_t pid, string input_cmd ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	print_symbol( pid, input_cmd );
} 


/**
 *	Check if we are at a watchpoint
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return If we should continue single-stepping 
 */
bool check_watchpts( pid_t pid ) {
	int flag = true;
	map< string, symbol_data >& symbol_table = all_functs[curr_function].symbol_table;

	for ( auto it = all_watchpts[curr_function].begin(); it != all_watchpts[curr_function].end(); ++it ) {
		symbol_data sym = symbol_table[it -> first];
		long data = get_data( pid, (void*)sym.addr );
		int size = sizeof_types[sym.type];
		
		// it -> second = watchpt_info object		
		long former_data = (it -> second).data;
		
		assert( ((it -> second).type == sym.type) && "Something went wrong, debugger terminating" );
		assert( (size == 8 || size == 4 || size == 2 || size == 1) && "Something went wrong, debugger terminating" );

		if ( size == 4 ) {
			data &= 0xFFFFFFFF;
			former_data &= 0xFFFFFFFF;
		}
		else if ( size == 2 ) {
			data &= 0xFFFF;
			former_data &= 0xFFFF;
		}
		else if ( size == 1 ) {		
			data &= 0xFF;
			former_data &= 0xFF;
		}
		
		if ( data != former_data ) {
			if ( !watch_line ) 				// if watch_line is 0 --- we must have put breakpt on the variable
				watch_line = addr_to_line[ former_brkpt.orig_addr ];
			
			flag = false;
			cerr << "\nWatchpoint '" << it -> first << "', " << curr_function << "() at " << filename << ":" << watch_line << "\n";
			cerr << "Former value = ";
			print_types( pid, former_data, sym.type );
			cerr << "New value = ";
			print_types( pid, data, sym.type );
			(it -> second).data = data;					// set new data to former data
			
			if ( !(it -> second).times_hit )				// first time hit
				cerr << "*** Initial (Former) value may have been garbage ***\n";
			
			cerr << "Value changed on line: " << watch_line << "\t" << sourceFile[watch_line] << "\n";						
			(it -> second).times_hit += 1;
		}
	}
	
	void* instr_addr = get_instr_ptr( pid );
	watch_line = addr_to_line[instr_addr];

	return flag;
}


/**
 *	Handler for setting a watchpoint
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param input_cmd: The symbol that we want to print
 */
void set_temp_watchpt( pid_t pid, string input_cmd ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	map< string, symbol_data >& symbol_table = all_functs[curr_function].symbol_table;
	auto it = symbol_table.begin();
	
	if ( (it = symbol_table.find(input_cmd)) != symbol_table.end() ) {
		if ( (it -> second).type < 12 ) {					// type of the symbol (cannot be char* or string)
			if ( watchpt_batch.find(input_cmd) == watchpt_batch.end() && all_watchpts[curr_function].find(input_cmd) == all_watchpts[curr_function].end() ) {
				++watchpt_num;
				watchpt_batch.insert(input_cmd);					// need to remove from both if we are removing
				watchpt_idx[curr_function][watchpt_num] = input_cmd;
				helper_watchpt[curr_function][input_cmd] = watchpt_num;
				cerr << "Watchpoint set at '" << input_cmd << "'\n";
			}
			else {
				cerr << "Watchpoint already set at '" << input_cmd << "'\n";
			}
		}
		else {
			cerr << "Cannot set watchpoint at '" << input_cmd << "', type not acceptable --- see help\n";
		}
	}
	else {
		cerr << "Cannot find variable: '" << input_cmd << "'\n";
	}
}


/**
 *	Helper to handle stepping
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return If we should continue single-stepping
 */
bool step_handler( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( addr_to_line.find(instr_addr) == addr_to_line.end() ) {
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		return true;
	}
	
	int line_num = addr_to_line[instr_addr];	
	
	if ( line_num == former_line ) {				// need to go to next line that is not the current one
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		return true;
	}
	
	switch_symbol_table( pid, line_num );
	
	if ( check_watchpts(pid) )	 			
		cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";	
	else cerr << "\nCurrent line: " << line_num << "\t\t" << sourceFile[line_num]	<< "\n";
	
	return false;
}


/**
 *	Helper to handle stepping with active watchpoints ~ above
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return If we should continue single-stepping
 */
bool step_watch( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( addr_to_line.find(instr_addr) == addr_to_line.end() ) {
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		return true;
	}
	
	int line_num = addr_to_line[ instr_addr ];
	switch_symbol_table( pid, line_num );

	return false;
}


/**
 *	Command handler
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param is_init_stop: Whether we are at the very beginning of our program or not (first stop)
 */
void prog_active( pid_t pid, bool is_init_stop ) {
	if ( is_init_stop ) {
		printIntro();
		cerr << "Program stopped\n";
	}
	else {
		if ( watchpt_exist() ) {				// continue through watchpoint	
			if ( reset_brkpt ) {		
				set_brkpt( pid, former_brkpt.orig_addr, false );
				reset_brkpt = false;	
			}

			if ( is_brkpt(pid) ) {
				brkpt_handler( pid, false );
				check_watchpts( pid );
			}
			else if ( is_brkpt_step(pid) ) {			// must be stepping through breakpt
				brkpt_handler( pid, true );
				check_watchpts( pid );
			}
			else {					// not breakpoints
				if ( step_flag ) {
					if ( step_handler(pid) ) 
						return;	
				}
				else {
					if ( step_watch(pid) ) 
						return;

					if ( check_watchpts(pid) ) {
						ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
						return;
					}
				}
			}
		}
		else {					// no active watchpoints
			// they continued through a breakpoint
			if ( cont_flag && reset_brkpt ) {	
				set_brkpt( pid, former_brkpt.orig_addr, false );	
				reset_brkpt = false;		
				ptrace( PTRACE_CONT, pid, NULL, NULL );						
		
				if ( !is_brkpt(pid) )			// if we are not currently at a breakpoint, we continue
					return;
			}
			else if ( reset_brkpt ) {			// they singlestepped past a breakpoint, reset here
				set_brkpt( pid, former_brkpt.orig_addr, false );
				reset_brkpt = false;	
			}
			
			if ( is_brkpt(pid) ) {
				brkpt_handler( pid, false );
			}
			else if ( is_brkpt_step(pid) ) {			// is stepping through a breakpoint
				brkpt_handler( pid, true );
			}
			else {				// stepping through
				// stepped through to the next line number 
				if ( step_handler(pid) ) 
					return;
			}
		}
		
		// used to determine which symbol table to use
		void* instr_addr = get_instr_ptr( pid );
		int line_num = addr_to_line[ instr_addr ];
		
		// check to see if we should switch out the symbol table
		switch_symbol_table( pid, line_num );		
	}

	cerr << "(sdb) ";
	
	// handle setting breakpoints and such here
	string input_cmd;

	while ( getline(cin, input_cmd) ) {
		// make command lowercase
		for ( int i = 0; i < input_cmd.length(); ++i ) {
			if ( input_cmd[i] == ' ' )
				break;
			else input_cmd[i] = tolower( input_cmd[i] );
		}
		
		trim( input_cmd );
	
		if ( !input_cmd.compare("run") || !input_cmd.compare("r") ) {
			if ( is_init_stop ) 
				break;
			
			cerr << "The program is already being run\n";
		}
		else if ( input_exit(input_cmd) ) {					// kill program
			if ( confirm_exit() ) {
				kill( pid, SIGKILL ); 
				break;
			}
			else {
				cerr << "Did not quit debugger\n";
			}
		}
		else if ( input_break(input_cmd) ) {
			handle_brk_or_rm( pid, input_cmd, true );
		}
		else if ( input_rm(input_cmd) ) {				
			handle_brk_or_rm( pid, input_cmd, false );
		}
		else if ( input_rm_watch(input_cmd) ) {		
			handle_rm_watch( pid, input_cmd );
		}
		else if ( input_watch(input_cmd) ) {
			set_temp_watchpt( pid, input_cmd );
		}
		else if ( input_print(input_cmd) ) {
			if ( is_init_stop ) 
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			else handle_print( pid, input_cmd );
		}
		else if ( !input_cmd.compare("info") || !input_cmd.compare("i") ) {
			print_allpt_info();
		}
		else if ( !input_cmd.compare("help") ) {
			printHelp();
		}
		else if ( !input_cmd.compare("continue") || !input_cmd.compare("c") ) {
			if ( is_init_stop ) {
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			}
			else {
				cont_flag = true;
				step_flag = false;
				break;
			}
		}
		else if ( input_next(input_cmd) ) {
			if ( is_init_stop ) {
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			}
			else {					
				former_line = get_linenum( pid );
				cont_flag = false;
				step_flag = true;
				break;
			}
		}
		else if ( !input_cmd.compare("reg") || !input_cmd.compare("registers") || !input_cmd.compare("regs") ) {
			if ( is_init_stop ) {
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			}
			else {	
				getRegisters( pid );
				printRegisters( pid );
			}
		}
		else {
			cerr << "Invalid command. Look at 'help' for a list of valid commands and usage\n";
		}
		
		cerr << "(sdb) ";
	}
	
	// insert breakpoints
	insert_brkpt_batch( pid );

	if ( is_init_stop ) {
		set_brkpt_main( pid );			// set breakpoint at main to build symbol table
		ptrace( PTRACE_CONT, pid, NULL, NULL );
	}
	else {
		// insert watchpoints --- should not insert if it is at initial stop
		insert_watchpt_batch( pid );
	
		if ( !watchpt_exist() ) {
			if ( cont_flag ) {
				if ( reset_brkpt ) 
					ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
				else ptrace( PTRACE_CONT, pid, NULL, NULL );
			}
			else {
				ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
			}
		}
		else {
			ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		}
	}
}


/**
 *	The beginning of our program
 *
 * 	@param argc: Arguments passed straight from original main function
 * 	@param argv: Arguments passed straight from original main function
 * 	@return Used for exit status checking
 */
int main_debugger( int argc, char* argv[] ) {
	curr_function = "main";

	pid_t parent = fork();

	assert( parent != -1 && "Forking for main debugger failed" );

	if ( parent ) {
		int	status;
		waitpid( parent, &status, 0 );

		// will send SIGTRAP at first execvp	  ---		stops before the program is run
		if ( WIFSTOPPED(status) ) {
			if ( WSTOPSIG(status) == SIGTRAP ) 				// before execve
				prog_active( parent, true );					// let the user set breakpoints and do other things
		}
		
		// wait again at the last address of main
		waitpid( parent, &status, 0 );
		
		// singlestep so we know that base pointer will be set to the correct value
		if ( WIFSTOPPED(status) ) {
			if ( WSTOPSIG(status) == SIGTRAP ) {		
				void* instr_addr = get_instr_ptr( parent );
	
				auto it = all_brkpts.find( instr_addr - 1 );
				assert( (it != all_brkpts.end()) && "Something went wrong, debugger terminating" );
	
				// restore main
				brkpt_info main_brkpt = all_brkpts[instr_addr - 1];
				handle_brkpt( parent, main_brkpt.orig_addr, (void*)main_brkpt.former_data );
				
				// single step to next instruction 
				ptrace( PTRACE_SINGLESTEP, parent, NULL, NULL );
			}
		}
		
		// now base pointer is absolutely set so we construct symbol table
		waitpid( parent, &status, 0 );
		
		assert( !curr_function.compare("main") && "Something went wrong, debugger terminating" );
		
		// breakpoint we put in to create the symbol table
		if ( WIFSTOPPED(status) ) {
			if ( WSTOPSIG(status) == SIGTRAP ) 		
				build_symbol_table( parent, curr_function );		
		}

		do {
			waitpid( parent, &status, 0 );

			if ( WIFEXITED(status) || (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL) ) 
				break;

			if ( WIFSTOPPED(status) ) {
				if ( WSTOPSIG(status) == SIGTRAP ) 
					prog_active(parent, false);
			}
		}
		while ( !WIFEXITED(status) );

		// can have option to rerun stuff
		cerr << "\nProgram finished - debugger terminating...\n";
	}
	else {
		prctl( PR_SET_PDEATHSIG, SIGHUP );				// kill child if parent terminates
	
		// begin pTrace of child process
		if ( ptrace(PTRACE_TRACEME, 0, NULL, NULL) ) {
			cerr << "Cannot trace child process for main debugger\n";
			exit( 1337 );
		}

		int k = execvp( argv[1], &argv[1] );

		assert( (k != -1) && "Execution failed for main debugger" );
	}	

	return 0;
}
