/**
 * 	@file: pTrace
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

using namespace std;

// struct for registers
struct user_regs_struct regs;


// --------------- WATCHPOINTS --------------------


// stores the watch variable data --- only non char* for now, cannot change char* anyways
struct watchpt_info {
	long data;					// *** make sure to cast before comparing in case
	int type;
	int times_hit;			// first time hit, we give them warning message about garbage
};

// map to store all info about watchpoints
// stores actual instruction address
// can be wrong if initial value is garbage --- give them note
map< string, watchpt_info > all_watchpts;				// variable name, watchpoint info

// used for inserting batches of watchpoints
set< string > watchpt_batch;

// map to store index of watchpoint
map< int, string > watchpt_idx;				// breakpoint number, variable name

// the number of watchpoints
int watchpt_num;

// if we have a watch command provided
bool watch_provided;

// map for our symbol table
// symbol (variable name), addr, type
map< string, pair<void*, int> > symbol_table;	


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
// memory address to breakpoint number
map< void*, int > helper_brkpt;				// address, breakpoint number
map< int, void* > brkpt_idx;				// breakpoint number, address

// used for inserting batches of breakpoints
set< void* > brkpt_batch;

// the number of breakpoints
int brkpt_num;

// used to calculate new breakpoints
//int last_used_brkpt;

// used for resetting the breakpoint
bool reset_brkpt;
brkpt_info former_brkpt;
bool cont_flag; 


// stores the former line number for stepping
int former_line;

// base pointer for getting variables
//void* base_ptr;	


/**
 *	All valid input commands for our pTrace-debugger
 *
 */
string cont_cmds[] = {"c", "continue"};
string next_cmds[] = {"n", "next", "s", "step"};
string exit_cmds[] = {"kill", "quit", "q", "exit"};

string reg_cmds[] = {"reg", "registers"};
string help_cmds[] = {"help"};

string run_cmds[] = {"run", "r"};

string break_cmds[] = {"break", "br", "b", "brk"};
string rm_brk_cmds[] = {"rm", "remove", "d", "delete"};
string watch_cmds[] = {"watch", "w"};

string info_brk_cmds[] = {"info", "i"};
string print_cmds[] = {"print", "p"};

// sed -i -e 's/cout/cerr/g' tryingPtrace.cpp to replace cout with cerr


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
 * 	@return The data at the specified address (will be size of void*)
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
 */
bool is_brkpt_step( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( all_brkpts.find(instr_addr) != all_brkpts.end() )		
		return true;
	
	return false;
}


/**
 *	Prints the intro for our pTrace-debugger
 *
 */
void printIntro() {
	//cerr << "\e[1m\n *** Welcome to sdb, copyright (c) 2016 Guiping Xie ***\n\n";
	cerr << "\e[1m\n *** Welcome to sdb ***\n\n";
	cerr << "Start / Run your program with 'r' or 'run'\n";
	cerr << "Set breakpoints with 'break', 'br', or 'b' along with the line number or function\n";
	cerr << "Set watchpoints with 'watch' or 'w' along with the variable name\n";
	cerr << "Delete break/watch points with 'clear', 'rm', 'remove', 'd', or 'delete'\n\t";
	cerr << "\talong with the line number, function, or variable name\n";
	cerr << "Look up your active break/watch points with 'i' or 'info'\n";
	cerr << "Continue your program with 'c' or 'continue'\n";
	cerr << "Step through your program line by line with 'n', 'next', 's', or 'step'\n";
	cerr << "Stop debugging your program with 'kill', 'q', 'quit', or 'exit'\n";
	cerr << "Print variable values with 'print' or 'p' along with the variable name\n";
	cerr << "\tprint value may be garbage if variable is not currently in scope\n";
	cerr << "For more advanced features type 'help' to get the complete functionality of sdb\e[0m\n\n"; 
}


/**
 *	Prints out information
 *
 */
void printHelp() {

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
 *	Checks whether the input is a valid function   ---   not implimenting functions now (placeholder)
 *
 * 	@param input: A string of characters to check whether it is a valid function
 * 	@return True if the input is a valid function
 */
bool is_valid_func( string &input ) {
	return true;
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
 *	Finds the breakpoint location, used for setting breakpoints
 *
 * 	@param str: The line number / function name encoded in a string
 * 	@param is_line_num: Whether the breakpoint is at a line number of function
 */
void find_print_brk_loc( string &str, bool is_line_num ) {
	if ( is_line_num ) {
		int line_num = stoi( str );
		auto it = line_to_addr.begin();
		
		// if we can find the address of the line (it corresponds to a line number in the source file)
		if ( (it = line_to_addr.find(line_num)) != line_to_addr.end() ) {
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) {
				++brkpt_num;
				cerr << "Breakpoint " << brkpt_num << " set at address: '" << it -> second << "', file: '";
				cerr << filename << "', line: '" << line_num << "'\n";
				helper_brkpt[it -> second] = brkpt_num;
				brkpt_idx[brkpt_num] = it -> second;
				brkpt_batch.insert( it -> second );
			}
			else {
				cerr << "Breakpoint already set at this address, breakpoint request ignored\n";
			}
		}
		else if ( (it = line_to_addr.lower_bound(line_num)) != line_to_addr.end() ) {
			
			// if we do not match any of the line numbers, we put it at the first line after the requested line
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) {
				++brkpt_num;
				cerr << "Was not able to find line number, inserting at next available point instead\n";
				cerr << "Breakpoint " << brkpt_num << " set at address: '" << it -> second << "', file: '";
				cerr << filename << "', line: '" << addr_to_line[it -> second] << "'\n";
				helper_brkpt[it -> second] = brkpt_num;
				brkpt_idx[brkpt_num] = it -> second;
				brkpt_batch.insert( it -> second );
			}
			else {
				cerr << "Breakpoint already set at a later address, breakpoint request ignored\n";
			}
		}
		else {
			cerr << "Line number is past end of file, breakpoint not set\n";
		}
	}
	else {
		// is function name
		
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
	if ( is_line_num ) {
		int line_num = stoi( str );
			
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
				if ( (all_brkpts_it = all_brkpts.find(line_it -> second)) != all_brkpts.end() ) {
					brkpt_info temp = all_brkpts_it -> second;
					//handle_brkpt( pid, temp.orig_addr, (void*)temp.former_data );
					
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
	else {
		// is function name
		
	}
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
			cerr << "    " << it -> first << "\t     breakpoint\t\t" << it -> second << "\t" << filename;
			cerr << ":" << addr_to_line[it -> second] << "\n";
		}
		
		cerr << "\n";
	}
	
	if ( !watchpt_idx.size() ) {
		cerr << "No active watchpoints are set\n\n";
	}
	else {
		cerr << "  Number\tType\t\tName\n";
		for ( auto it = watchpt_idx.begin(); it != watchpt_idx.end(); ++it ) 
			cerr << "    " << it -> first << "\t     watchpoint\t\t" << it -> second << "\n";
		cerr << "\n";	
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
		brkpt_batch.erase( it++ /* makes a copy and destroys current it */ );
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
	cerr << "\nBreakpoint " << helper_brkpt[new_instr_addr] << ", at " << filename << ":" << line_num << "\n";
	cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";		

	// need to handle breakpoint
	brkpt_info curr_brkpt = all_brkpts[new_instr_addr];
	handle_brkpt( pid, curr_brkpt.orig_addr, (void*)curr_brkpt.former_data );	
	
	// indicate we need to reset this breakpoint
	reset_brkpt = true;
	former_brkpt = curr_brkpt;
}


/**
 *	Sets a breakpoint at main so we can build a symbol table (from the base pointer)
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void set_brkpt_main( pid_t pid ) {
	set_brkpt( pid, break_main_addr, true );			
}


/**
 *	Checks if we are breaking at main
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@return If we are at the beginning of our main function
 */
bool is_brkpt_main( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );
	return ( instr_addr - 1 == break_main_addr );
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
	
	} while ( flag && idx < 4096 /* arbitrary bound */ );
	
	if ( idx == 4096 ) {				// is this necessary?
		cerr << "String is too big (over 4096 bytes) - make sure to null terminate\n";
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
 *	Fills the symbol table with our symbols (parsed from objdump)
 * 
 */
void fill_symbols( pid_t pid ) {
	void* base_ptr = get_base_ptr( pid );
	
	for ( auto it = all_symbols.begin(); it != all_symbols.end(); ++it ) {
		symbol_data symbol_info = it -> second;
		
		if ( symbol_table.find(it -> first) == symbol_table.end() ) {
			void* symbol_addr = (void*)( (long)base_ptr + symbol_info.offset );
			pair< void*, int > addr_type = make_pair( symbol_addr, symbol_info.type );
			symbol_table[it -> first] = addr_type;
		}
		else {				// should never get here
			cerr << "Error - Duplicate results in the symbol table\n";
		}
	}
}


/**
 *	Print the symbol (variable name) value which is passed in, should be in scope
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param symbol: The symbol that we want to print
 */
void print_symbol( pid_t pid, string &symbol ) {
	auto it = symbol_table.begin();
	if ( (it = symbol_table.find(symbol)) != symbol_table.end() ) {
		pair< void*, int > symbol_info = it -> second;
		int type_idx = symbol_info.second;
		
		// check types
		long data = get_data( pid, symbol_info.first );
		//cout << data << "\n";
		
		// manual printing --- NOT portable
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
			cerr << data_double << "\n";
		}
		else if ( type_idx == 7 ) {
			// convert to double
			double data_double;
			memcpy( &data_double, &data, sizeof(double) );
			cerr << data_double << "\n";
		}
		else if ( type_idx == 8 ) {
			// convert to float
			float data_float;
			memcpy( &data_float, &data, sizeof(float) );
			cerr << data_float << "\n";
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
		else if ( type_idx == 13 ) {
			// cannot do strings currently
			
		}
		else {				// should never reach
			cerr << "Error - debugger failed\n";
		}
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
 *	Handler for setting a watchpoint
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param input_cmd: The symbol that we want to print
 */
void set_watchpt( pid_t pid, string input_cmd ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	
	if ( symbol_table.find(input_cmd) != symbol_table.end() ) {
		if ( watchpt_batch.find(input_cmd) == watchpt_batch.end() ) {
			++watchpt_num;
			watchpt_batch.insert(input_cmd);
			watchpt_idx[watchpt_num] = input_cmd;
			watch_provided = true;
			cerr << "Watchpoint set at '" << input_cmd << "'\n";
		}
		else {
			cerr << "Watchpoint already set at '" << input_cmd << "'\n";
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
		 			
	cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";	
	
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
		if ( is_brkpt_main(pid) ) {
			// restore main
			brkpt_info main_brkpt = all_brkpts[break_main_addr];
			handle_brkpt( pid, main_brkpt.orig_addr, (void*)main_brkpt.former_data );	
			
			// get and fill all the symbols from the base pointer
			fill_symbols( pid );
			
			ptrace( PTRACE_CONT, pid, NULL, NULL );
			return;
		}
		
		// they continued through a breakpoint
		if ( cont_flag && reset_brkpt ) {	
			set_brkpt( pid, former_brkpt.orig_addr, false );	
			reset_brkpt = false;			
			ptrace( PTRACE_CONT, pid, NULL, NULL );					
		
			if ( !is_brkpt(pid) )
				return;
		}
		else if ( reset_brkpt ) {			// they singlestepped through a breakpoint
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
	
	cerr << "(sdb) ";
	
	// handle setting breakpoints and such here
	string input_cmd;

	while ( getline(cin, input_cmd) ) {
		// make input lowercase
		//str_to_lower( input_cmd );
		for ( int i = 0; i < input_cmd.length(); ++i ) {
			if ( input_cmd[i] == ' ' )
				break;
			else input_cmd[i] = tolower( input_cmd[i] );
		}
	
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
		else if ( input_rm(input_cmd) ) {							// need to handle watchpoints
			// also check if we have no more watchpoints so we do not have to singlestep
			handle_brk_or_rm( pid, input_cmd, false );
		}
		else if ( input_watch(input_cmd) ) {
			if ( is_init_stop ) 
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			else set_watchpt( pid, input_cmd );
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
				break;
			}
		}
		else if ( !input_cmd.compare("reg") || !input_cmd.compare("registers") ) {
			if ( is_init_stop ) {
				cerr << "The program is not being run (input 'r' or 'run' to run)\n";
			}
			else {	
				getRegisters( pid );
				printRegisters( pid );
			}
		}
		else {
			cerr << "Invalid command. Do not include leading / trailing spaces. Look at 'help' for more info\n";
		}
		
		cerr << "(sdb) ";
	}
	
	// insert breakpoints
	insert_brkpt_batch( pid );

	if ( is_init_stop ) {
		set_brkpt_main( pid );
		ptrace( PTRACE_CONT, pid, NULL, NULL );
	}
	else {
		if ( cont_flag ) {
			if ( reset_brkpt ) 
				ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
			else ptrace( PTRACE_CONT, pid, NULL, NULL );
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
	pid_t parent = fork();

	if ( parent == -1 ) {
		cerr << "Forking for main debugger failed\n";			
		exit( 420 );
	}

	if ( parent ) {
		watch_provided = false;
		
		int	status;
		waitpid( parent, &status, 0 );

		// will send SIGTRAP at first execvp	  ---		stops before the program is run
		if ( WIFSTOPPED(status) ) {
			if ( WSTOPSIG(status) == SIGTRAP ) 				// before execve
				prog_active( parent, true );					// let the user set breakpoints and do other things
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
		// begin pTrace of child process
		if ( ptrace(PTRACE_TRACEME, 0, NULL, NULL) ) {
			cerr << "Cannot trace child process for main debugger\n";
			exit( 1337 );
		}

		// change so we can execute with -f flag   ---   getopt
		int k = execvp( argv[1], &argv[1] );

		if ( k == -1 )
			cerr << "Execution failed for main debugger\n";
		exit( 1337 );
	}	

	return 0;
}
