/**
 * 	@file: pTrace
 * 	@author: Guiping Xie 
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

using namespace std;

// struct for registers
struct user_regs_struct regs;

// stores the brekpoint instruction data so we can restore it later 
struct brkpt_info {
  long former_data;
  void* orig_addr;
  void* brkpt_addr;				// 1 more than original
};

// map to store all info about breakpoints
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
int last_used_brkpt;

// used for resetting the breakpoint
bool reset_brkpt;
brkpt_info former_brkpt;
bool cont_flag; 


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
string info_brk_cmds[] = {"info"};

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
	cerr << "Register rax:\t\t" << get_data( pid, ( void* )regs.rax ) << "\n";
	cerr << "Register rbx:\t\t" << get_data( pid, ( void* )regs.rbx ) << "\n";
	cerr << "Register rcx:\t\t" << get_data( pid, ( void* )regs.rcx ) << "\n";
	cerr << "Register rdx:\t\t" << get_data( pid, ( void* )regs.rdx ) << "\n";
	cerr << "Register rsi:\t\t" << get_data( pid, ( void* )regs.rsi ) << "\n";
	cerr << "Register rdi:\t\t" << get_data( pid, ( void* )regs.rdi ) << "\n";
	cerr << "Register rbp:\t\t" << get_data( pid, ( void* )regs.rbp ) << "\n";
	cerr << "Register rsp:\t\t" << get_data( pid, ( void* )regs.rsp ) << "\n";
	cerr << "Register r8:\t\t" << get_data( pid, ( void* )regs.r8 ) << "\n";
	cerr << "Register r9:\t\t" << get_data( pid, ( void* )regs.r9 ) << "\n";
	cerr << "Register r10:\t\t" << get_data( pid, ( void* )regs.r10 ) << "\n";
	cerr << "Register r11:\t\t" << get_data( pid, ( void* )regs.r11 ) << "\n";
	cerr << "Register r12:\t\t" << get_data( pid, ( void* )regs.r12 ) << "\n";
	cerr << "Register r13:\t\t" << get_data( pid, ( void* )regs.r13 ) << "\n";
	cerr << "Register r14:\t\t" << get_data( pid, ( void* )regs.r14 ) << "\n";
	cerr << "Register r15:\t\t" << get_data( pid, ( void* )regs.r15 ) << "\n";
	cerr << "Register rip:\t\t" << get_data( pid, ( void* )regs.rip ) << "\n";
	cerr << "Register eflags:\t" << get_data( pid, ( void* )regs.eflags ) << "\n";
	cerr << "Register cs:\t\t" << get_data( pid, ( void* )regs.cs ) << "\n";
	cerr << "Register ss:\t\t" << get_data( pid, ( void* )regs.ss ) << "\n";
	cerr << "Register ds:\t\t" << get_data( pid, ( void* )regs.ds ) << "\n";
	cerr << "Register es:\t\t" << get_data( pid, ( void* )regs.es ) << "\n";
	cerr << "Register fs:\t\t" << get_data( pid, ( void* )regs.fs ) << "\n";
	cerr << "Register gs:\t\t" << get_data( pid, ( void* )regs.gs ) << "\n\n";
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
	//cout << instr_ptr << "  " << data << "\n";
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
 *	Prints the intro for our pTrace-debugger
 *
 */
void printIntro() {
	cerr << "\e[1m\n *** Welcome to sdb ***\n\n";
	cerr << "Start / Run your program with 'r' or 'run'\n";
	cerr << "Set breakpoints with 'break', 'br', or 'b' along with the line number or function\n";
	cerr << "Delete breakpoints with 'clear', 'rm', 'remove', 'd', or 'delete'\n\t";
	cerr << "\talong with the line number or function\n";
	cerr << "Look up your active breakpoints with 'i' or 'info'\n";
	cerr << "Continue your program with 'c' or 'continue'\n";
	cerr << "Step through your program line by line with 'n', 'next', 's', or 'step'\n";
	cerr << "Stop debugging your program with 'kill', 'q', 'quit', or 'exit'\n";
	cerr << "For more advanced features type 'help' to get the complete functionality of sdb\e[0m\n\n"; 
}


/**
 *	Prints out information
 *
 */
void printHelp() {

}


/**
 *	Checks whether the input is a valid line number
 *
 * 	@param input: A string of characters to check whether it is a valid number 
 * 	@return True if the input is a valid number
 */
bool is_num( string input ) {
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
bool is_valid_func( string input ) {
	return true;
}


/**
 *	Checks whether the command provided is a 'next' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'next' command was provided
 */
bool input_next( string input ) {	
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
bool input_break( string input ) {
	if ( !input.find("break ") || !input.find("br ") || !input.find("b ") || !input.find("brk ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'remove' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'remove' command was provided
 */
bool input_rm( string input ) {
	if ( !input.find("rm ") || !input.find("remove ") || !input.find("clear ") || !input.find("d ") || !input.find("delete ") ) 
		return true;

	return false;
}


/**
 *	Checks whether the command provided is a 'exit' command
 *
 * 	@param input: A string representing a command
 * 	@return True if a 'exit' command was provided
 */
bool input_exit( string input ) {
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
 *	Gets the index of the last batch of added breakpoints
 *		breakpoints are added in batches 
 *			(only after user requests to continue with the 'continue' command)
 *
 * 	@return The beginning index of the current batch of breakpoints
 */
int get_last_added_brkpts() {
	int ret = last_used_brkpt;
	last_used_brkpt = brkpt_num;
	return ret + 1;
}


/**
 *	Finds the breakpoint location, used for setting breakpoints
 *
 * 	@param str: The line number / function name encoded in a string
 * 	@param is_line_num: Whether the breakpoint is at a line number of function
 */
void find_print_brk_loc( string str, bool is_line_num ) {
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
 * 	@param str: The line number / function name encoded in a string
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param is_line_num: Whether the breakpoint is at a line number of function
 */
void find_print_rm_loc( string str, pid_t pid, bool is_line_num ) {
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
					handle_brkpt( pid, temp.orig_addr, (void*)temp.former_data );

					void* instr_addr = get_instr_ptr( pid );
					
					// check if we are currently stopped at this breakpoint we want to remove
					if ( instr_addr == line_it -> second ) 
						reset_brkpt = false;
					
					all_brkpts.erase(all_brkpts_it);			// delete it at the end
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
 * 	@param input_cmd: The line number / function name encoded in a string
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param in_break: Whether we are inserting a breakpoint or not, true = inserting
 */
void handle_brk_or_rm( string input_cmd, pid_t pid, bool in_break /* true: is setting brkpt */ ) {
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
			else find_print_rm_loc( input_cmd, pid, true );	
		}
	}
	else {
		if ( is_valid_func(input_cmd) ) {					// check if it is a function
			if ( in_break )
				find_print_brk_loc( input_cmd, false );
			else find_print_rm_loc( input_cmd, pid, false );	
		}
	}
}


/**
 *	Prints out all breakpoint infomation, called when user inputs 'info' command
 *
 */
void print_brkpt_info() {
	if ( !helper_brkpt.size() ) {
		cerr << "No active breakpoints are set\n";
	}
	else {
		cerr << "  Number\tType\t\tAddress\t\tLocation\n";
		
		for ( auto it = helper_brkpt.begin(); it != helper_brkpt.end(); ++it ) {
			cerr << "    " << it -> second << "\t     breakpoint\t\t" << it -> first << "\t" << filename;
			cerr << ":" << addr_to_line[it -> first] << "\n";
		}
	}
}


/**
 *	Inserts all the breakpoints, called after user provided 'continue' command
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void insert_brkpt_batch( pid_t pid ) {
/*
	int start_idx = get_last_added_brkpts();

	// insert break points here
	for ( auto it = brkpt_idx.find(start_idx); it != brkpt_idx.end(); ++it ) 
		set_brkpt( pid, it -> second, true );
*/
	for ( auto it = brkpt_batch.begin(); it != brkpt_batch.end(); ) {
		set_brkpt( pid, *it, true );
		brkpt_batch.erase( it++ /* makes a copy and destroys current it */ );
	}
}


/**
 *	Helper to handle breakpoints
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void brkpt_handler( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	// since we are 1 past due to INT 3, we need to decrement
	void* new_instr_addr = instr_addr - 1;

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


bool still_in_addr( void* addr, int idx ) {
	x86 temp = x86_code[idx];
	vector< individ_x86 > all_addrs = temp.assembly;
	
	for ( int i = 0; i < all_addrs.size(); ++i ) {
		if ( addr == all_addrs[i].addr )
			return true;
	}
	
	return false;
}


/**
 *	Helper to handle stepping --- currently not working
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
bool step_handler( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );
	//cerr << instr_addr << "\n";
	if ( addr_to_line.find(instr_addr) == addr_to_line.end() ) {
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		return false;
		//cerr << instr_addr << "\n";
		//usleep(10000);
	}
	
	int line_num = addr_to_line[instr_addr];				
	cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";	
	
	return ( line_num >= sourceFile.size() - 1 );
}


/**
 *	Command handler
 *
 * 	@param pid: Process ID of the child (debuggee) 
 * 	@param is_init_stop: Whether we are stopping at the very beginning of our program or not (first stop)
 *
 * 	@return If we should stop our process
 */
bool prog_active( pid_t pid, bool is_init_stop ) {
	if ( is_init_stop ) {
		printIntro();
		cerr << "Program stopped\n";
	}
	else {
		// they continued through a breakpoint
		if ( cont_flag && reset_brkpt ) {	
			set_brkpt( pid, former_brkpt.orig_addr, false );	
			reset_brkpt = false;			
			ptrace( PTRACE_CONT, pid, NULL, NULL );					
		
			if ( !is_brkpt(pid) )
				return false;
		}
		else if ( reset_brkpt ) {			// they singlestepped through a breakpoint
			set_brkpt( pid, former_brkpt.orig_addr, false );
			reset_brkpt = false;	
		}

		if ( is_brkpt(pid) ) {
			brkpt_handler( pid );
		}
		else {				// stepping through
			// stepped through to the next line number
			if ( step_handler(pid) ) {
				kill( pid, SIGKILL ); 
				return true;
			}
		}
	}
	
	cerr << "(sdb) ";
	
	// handle setting breakpoints and such here
	string input_cmd;

	while ( getline(cin, input_cmd) ) {
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
				cerr << "Did not quit program\n";
			}
		}
		else if ( input_break(input_cmd) ) {
			handle_brk_or_rm( input_cmd, pid, true );
		}
		else if ( input_rm(input_cmd) ) {
			handle_brk_or_rm( input_cmd, pid, false );
		}
		else if ( !input_cmd.compare("info") || !input_cmd.compare("i") ) {
			// extend to watchpoints
			print_brkpt_info();
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
	
	// need method to set better breakpoint
	// insert breakpoints
	insert_brkpt_batch( pid );

	if ( is_init_stop ) {
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
	
	return false;
}


/**
 *	The beginning of our program
 *
 * 	@param argc: Arguments passed straight from original main function
 * 	@param argv: Arguments passed straight from original main function
 *
 * 	@return Used for exit status checking
 */
int main_debugger( int argc, char* argv[] ) {
	pid_t parent = fork();

	if ( parent == -1 ) {
		cerr << "Forking for main debugger failed\n";			
		exit( 420 );
	}

	if ( parent ) {
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
				if ( WSTOPSIG(status) == SIGTRAP ) {
					//cerr << get_instr_ptr( parent ) << "\n";
					if ( prog_active(parent, false) )
						break;
				}
				else {
					cout << "NOT SIGTRAP\n";
				}
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
