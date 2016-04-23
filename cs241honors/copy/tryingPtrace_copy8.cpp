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
map< void*, brkpt_info > all_brkpts;

// abstraction for real breakpoint
// memory address to breakpoint number
map< void*, int > helper_brkpt;
map< int, void* > brkpt_idx;

// the number of breakpoints
int brkpt_num;

// used to calculate new breakpoints
int last_used_brkpt;

// used for resetting the breakpoint
bool reset_brkpt;
brkpt_info former_brkpt;
bool cont_flag; 

// used for stepping through 
int former_linenum;

// helpers to get stuff
void* get_instr_ptr( pid_t pid ) {
	return (void*)ptrace( PTRACE_PEEKUSER, pid, 8 * RIP, NULL );
}

void set_instr_ptr( pid_t pid, void* addr ) {
	ptrace( PTRACE_POKEUSER, pid, 8 * RIP, addr );
}

void* get_stack_ptr( pid_t pid ) {
	return (void*)ptrace( PTRACE_PEEKUSER, pid, 8 * RSP, NULL );
}

void* get_ret_addr( pid_t pid, void* stack_pointer ) {
	return (void*)ptrace( PTRACE_PEEKTEXT, pid, stack_pointer, NULL );
}

long get_data( pid_t pid, void* addr ) {
	return ptrace( PTRACE_PEEKDATA, pid, addr, NULL );
}

void set_data( pid_t pid, void* addr, void* data ) {
	ptrace( PTRACE_POKEDATA, pid, addr, data );
}

void getRegisters( pid_t pid ) {
	ptrace( PTRACE_GETREGS, pid, NULL, &regs );
}

// sed -i -e 's/cout/cerr/g' tryingPtrace.cpp to replace cout with cerr

// prints the registers gdb prints
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


// create breakpoint
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

	if ( is_new_brkpt ) {
		// need to store the former instruction pointer and data
		brkpt_info storage;
		storage.former_data = former_data;
		storage.orig_addr = addr;
		storage.brkpt_addr = addr + 1;			// one past after opcode
		all_brkpts[addr] = storage;					// add in map
	}
}

// set back instruction pointer
void handle_brkpt( pid_t pid, void* instr_ptr, void* data ) {
	set_data( pid, instr_ptr, data );
	set_instr_ptr( pid, instr_ptr );
}


// check to see if the current brkpt_num instruction is a breakpoint
bool is_brkpt( pid_t pid ) {
	void* instr_addr = get_instr_ptr( pid );

	if ( all_brkpts.find(instr_addr - 1) != all_brkpts.end() )
		return true;
	
	return false;
}


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

void printHelp() {

}

string cont_cmds[] = {"c", "continue"};
string next_cmds[] = {"n", "next", "s", "step"};
string exit_cmds[] = {"kill", "quit", "q", "exit"};

string reg_cmds[] = {"reg", "registers"};
string help_cmds[] = {"help"};

string run_cmds[] = {"run", "r"};
string break_cmds[] = {"break", "br", "b", "brk"};
string rm_brk_cmds[] = {"rm", "remove", "d", "delete"};
string info_brk_cmds[] = {"info"};


// in break function
// check that input is now a line number
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

// in break function
// check that input is now a valid function   ---   not implimenting functions now (placeholder)
bool is_valid_func( string input ) {
	return true;
}

// check to see if the input is valid but not one of the commands to run / set breakpoints
bool input_valid( string input ) {
	for ( int i = 0; i < 2; ++i )
		if ( !input.compare(cont_cmds[i]) )
			return true;
			
	for ( int i = 0; i < 4; ++i )
		if ( !input.compare(next_cmds[i]) )
			return true;
			
	for ( int i = 0; i < 2; ++i )
		if ( !input.compare(reg_cmds[i]) )
			return true;
			
	return false;
}

// check to see if next command was provided
bool input_next( string input ) {	
	for ( int i = 0; i < 4; ++i )
		if ( !input.compare(next_cmds[i]) )
			return true;
			
	return false;
}

// check to see if break command was provided 
bool input_break( string input ) {
	if ( !input.find("break ") || !input.find("br ") || !input.find("b ") || !input.find("brk ") ) 
		return true;

	return false;
}

// check to see if a remove command was provided
bool input_rm( string input ) {
	if ( !input.find("rm ") || !input.find("remove ") || !input.find("clear ") || !input.find("d ") || !input.find("delete ") ) 
		return true;

	return false;
}

// check to see if exit command was provided
bool input_exit( string input ) {
	for ( int i = 0; i < 4; ++i )
		if ( !input.compare(exit_cmds[i]) )
			return true;

	return false;
} 

// confirm if the user wants to exit or not
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

// gets the index of the last added breakpoints
int get_last_added_brkpts() {
	int ret = last_used_brkpt;
	last_used_brkpt = brkpt_num;
	return ret + 1;
}

// find breakpoint and print out info about them
// in case of duplicates, we don't check until later --- maybe change
void find_print_brk_loc( string str, bool is_line_num ) {
	// in case if it does not match any line number
	// we put the brkpt at the next line greater than the line number specified
	// print message if that is the case			

	if ( is_line_num ) {
		int line_num = stoi( str );
		auto it = line_to_addr.begin();
		
		if ( (it = line_to_addr.find(line_num)) != line_to_addr.end() ) {
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) {
				++brkpt_num;
				cerr << "Breakpoint " << brkpt_num << " set at address: '" << it -> second << "', file: '";
				cerr << filename << "', line: '" << line_num << "'\n";
				helper_brkpt[it -> second] = brkpt_num;
				brkpt_idx[brkpt_num] = it -> second;
			}
			else {
				cerr << "Breakpoint already set at this address, breakpoint request ignored\n";
			}
		}
		else if ( (it = line_to_addr.lower_bound(line_num)) != line_to_addr.end() ) {
			if ( helper_brkpt.find(it -> second) == helper_brkpt.end() ) {
				++brkpt_num;
				cerr << "Was not able to find line number, inserting at next available point instead\n";
				cerr << "Breakpoint " << brkpt_num << " set at address: '" << it -> second << "', file: '";
				cerr << filename << "', line: '" << addr_to_line[it -> second] << "'\n";
				helper_brkpt[it -> second] = brkpt_num;
				brkpt_idx[brkpt_num] = it -> second;
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

// find and remove breakpoint and print out info
void find_print_rm_loc( string str, bool is_line_num ) {
	if ( is_line_num ) {
		int line_num = stoi( str );
			
		auto line_it = line_to_addr.begin();
		if ( (line_it = line_to_addr.find(line_num)) != line_to_addr.end() ) {
			auto it = helper_brkpt.begin();
		
			if ( (it = helper_brkpt.find(line_it -> second)) != helper_brkpt.end() ) {
				cerr << "Removing breakpoint at line: '" << line_num << "'\n";
				brkpt_idx.erase( it -> second );
				helper_brkpt.erase( it );				// delete
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

// handling setting or removing breakpoints
void handle_brk_or_rm( string input_cmd, bool in_break /* true: is setting brkpt */ ) {
	input_cmd.erase( 0, input_cmd.find(" ") + 1 );
	trim( input_cmd );
	
	if ( (input_cmd[0] == '-') ) {
		if ( in_break )
			cerr << "Line number is not valid, breakpoint not set\n";
		else cerr << "Line number is not valid\n";
	}
	else if ( isdigit(input_cmd[0]) ) {
		if ( is_num(input_cmd) ) { 
			if ( in_break )
				find_print_brk_loc( input_cmd, true );				// breakpoint print out handler
			else find_print_rm_loc( input_cmd, true );	
		}
	}
	else {
		if ( is_valid_func(input_cmd) ) {
			if ( in_break )
				find_print_brk_loc( input_cmd, false );
			else find_print_rm_loc( input_cmd, false );	
		}
	}
}

// print out all breakpoint info (line numbers and such)
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

void insert_brkpt_batch( pid_t pid ) {
	int start_idx = get_last_added_brkpts();

	// insert break points here
	for ( auto it = brkpt_idx.find(start_idx); it != brkpt_idx.end(); ++it ) 
		set_brkpt( pid, it -> second, true );
}

// when the program first stops to let the user input breakpoints
void prog_init( pid_t pid ) {
	printIntro();
	cerr << "Program stopped\n(sdb) ";			
	
	// handle setting breakpoints and such here
	string input_cmd;

	while ( getline(cin, input_cmd) ) {
		if ( !input_cmd.compare("run") || !input_cmd.compare("r") ) {
			break;
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
			handle_brk_or_rm( input_cmd, true );
		}
		else if ( input_rm(input_cmd) ) {
			handle_brk_or_rm( input_cmd, false );
		}
		else if ( !input_cmd.compare("info") || !input_cmd.compare("i") ) {
			print_brkpt_info();					// extend to watchpoints
		}
		else if ( !input_cmd.compare("help") ) {
			printHelp();
		}
		else if ( input_valid(input_cmd) ) {
			cerr << "The program is not being run (input 'r' or 'run' to run)\n";
		}
		else {
			cerr << "Invalid command. Do not include leading / trailing spaces. Look at 'help' for more info\n";
		}
		
		cerr << "(sdb) ";
	}

	// insert break points here
	insert_brkpt_batch( pid );

	ptrace( PTRACE_CONT, pid, NULL, NULL );
}

// when the program is active, stops to let the user manipulate program
void prog_active( pid_t pid ) {
	// they continued through a breakpoint
	if ( cont_flag && reset_brkpt ) {	
		set_brkpt( pid, former_brkpt.orig_addr, false );	
		reset_brkpt = false;			
		ptrace( PTRACE_CONT, pid, NULL, NULL );
		
		if ( !is_brkpt(pid) )
			return;
	}
	
	// they singlestepped through a breakpoint
	if ( reset_brkpt ) {
		set_brkpt( pid, former_brkpt.orig_addr, false );
		reset_brkpt = false;	
	}

	if ( is_brkpt(pid) ) {
		void* instr_addr = get_instr_ptr( pid );
		
		// since we are 1 past due to INT 3, we need to decrement
		void* new_instr_addr = instr_addr - 1;
		
		int line_num = addr_to_line[new_instr_addr];			
		cerr << "\nBreakpoint " << helper_brkpt[new_instr_addr] << ", at " << filename << ":" << line_num << "\n";
		cerr << line_num << "\t\t\t" << sourceFile[line_num] << "\n";		
		
		// need to handle breakpoint
		brkpt_info curr_brkpt = all_brkpts[new_instr_addr];
		handle_brkpt( pid, curr_brkpt.orig_addr, (void*)curr_brkpt.former_data );	
		reset_brkpt = true;
		former_brkpt = curr_brkpt;
		former_linenum = line_num;
	}
	else {				// stepping through
		// stepped through to the next line number
		++former_linenum;
		if ( former_linenum < sourceFile.size() ) 
			cerr << former_linenum << "\t\t\t" << sourceFile[former_linenum] << "\n";		
	}
	
	cerr << "(sdb) ";
	
	string input_cmd;

	while ( getline(cin, input_cmd) ) {
		if ( !input_cmd.compare("run") || !input_cmd.compare("r") ) {
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
			handle_brk_or_rm( input_cmd, true );
		}
		else if ( input_rm(input_cmd) ) {
			handle_brk_or_rm( input_cmd, false );
		}
		else if ( !input_cmd.compare("info") || !input_cmd.compare("i") ) {
			// extend to watchpoints
			print_brkpt_info();
		}
		else if ( !input_cmd.compare("help") ) {
			printHelp();
		}
		else if ( !input_cmd.compare("continue") || !input_cmd.compare("c") ) {
			cont_flag = true;
			break;
		}
		else if ( input_next(input_cmd) ) {
			cont_flag = false;
			break;
		}
		else if ( !input_cmd.compare("reg") || !input_cmd.compare("registers") ) {
			getRegisters( pid );
			printRegisters( pid );
		}
		else {
			cerr << "Invalid command. Do not include leading / trailing spaces. Look at 'help' for more info\n";
		}
		
		cerr << "(sdb) ";
	}
	
	// need method to set better breakpoint

	// insert breakpoints
	insert_brkpt_batch( pid );

	if ( cont_flag ) {
		if ( reset_brkpt ) 
			ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
		else ptrace( PTRACE_CONT, pid, NULL, NULL );
	}
	else {
		ptrace( PTRACE_SINGLESTEP, pid, NULL, NULL );
	}
}

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
				prog_init( parent );
		}

		do {
			waitpid( parent, &status, 0 );

			if ( WIFEXITED(status) || (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL) ) 
				break;

			if ( WIFSTOPPED(status) ) 
				if ( WSTOPSIG(status) == SIGTRAP )
					prog_active( parent );
		}
		while ( !WIFEXITED(status) );

		// can have option to rerun stuff
		cerr << "Program finished - debugger terminating...\n";
	}
	else {
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
