/**
 * 	@file: pTrace.h
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

#ifndef PTRACE_H 
#define PTRACE_H 
 
#include <string>
#include <vector>
#include <map>
#include <set>

#include <unistd.h>
#include <sys/user.h>

 
class Ptrace {
	private:
		// struct for registers
		struct user_regs_struct regs;

		// --------------- WATCHPOINTS --------------------


		// stores the watch variable data --- only non char* for now, cannot change char* anyways
		struct watchpt_info {
			long data;			
			int type;
			int times_hit;			// first time hit, we give them warning message about garbage
		};

		// map to store all info about watchpoints
		// function -> variable name, watchpoint info
		std::map< std::string, std::map<std::string, watchpt_info> > all_watchpts;				

		// used for inserting batches of watchpoints --- insert into curr_function
		std::set< std::string > watchpt_batch;

		// map to store index of watchpoint --- almost useless
		std::map< std::string, std::map<std::string, int> > helper_watchpt;		// function -> variable name, watchpoint number
		std::map< std::string, std::map<int, std::string> > watchpt_idx;				// function -> watchpoint number, variable name

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
		std::map< void*, brkpt_info > all_brkpts;				// address, breakpoint info

		// abstraction for real breakpoint
		// memory address to breakpoint number --- almost useless
		std::map< void*, int > helper_brkpt;				// address, breakpoint number
		std::map< int, void* > brkpt_idx;				// breakpoint number, address

		// used for inserting batches of breakpoints
		std::set< void* > brkpt_batch;

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
		std::string curr_function;
	
	
		/**
		 *	Command handler
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param is_init_stop: Whether we are at the very beginning of our program or not (first stop)
		 */
		void prog_active( pid_t pid, bool is_init_stop );
	
	
		/**
		 *	Helper to handle stepping with active watchpoints ~ above
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return If we should continue single-stepping
		 */
		bool step_watch( pid_t pid );
	
		
		/**
		 *	Helper to handle stepping
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return If we should continue single-stepping
		 */
		bool step_handler( pid_t pid );
	
		
		/**
		 *	Handler for setting a watchpoint
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param input_cmd: The symbol that we want to print
		 */
		void set_temp_watchpt( pid_t pid, std::string input_cmd );
	
		
		/**
		 *	Check if we are at a watchpoint
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return If we should continue single-stepping 
		 */
		bool check_watchpts( pid_t pid );
		
		
		/**
		 *	Handler for when the user provides the 'print' command
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param input_cmd: The symbol that we want to print
		 */
		void handle_print( pid_t pid, std::string input_cmd );
		
		
		/**
		 *	Print the symbol (variable name) value which is passed in, should be in scope
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param symbol: The symbol that we want to print
		 */
		void print_symbol( pid_t pid, std::string &symbol );
		
		
		/**
		 *	Print the data represented as the passed in type
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param data: The data we want to print
		 * 	@param type_idx: The integer corresponding to a type in the type array
		 */
		void print_types( pid_t pid, long data, int type_idx );
		
		
		/**
		 *	Prints the string pointed to by the char pointer
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param text_addr: The address the char pointer is pointing to
		 */
		void print_char_sym( pid_t pid, long text_addr );
		
		
		/**
		 *	Finds the location of main and sets a breakpoint there
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void set_brkpt_main( pid_t pid );
		
		
		/**
		 *	Helper to switch out the current symbol table (if we do)
		 *
		 * 	@param pid: Process ID of the child (debuggee)
		 * 	@param line_num: The current line number we want to check
		 */
		void switch_symbol_table( pid_t pid, int line_num );
		
		
		/**
		 *	Builds the symbol table - called after initial stop
		 *
		 * 	@param pid: Process ID of the child (debuggee)
		 * 	@param function: The function corresponding to the symbol table 
		 */
		void build_symbol_table( pid_t pid, std::string function );

		
		/**
		 *	Fills the symbol table with our symbols (parsed from objdump)
		 * 
		 * 	@param pid: Process ID of the child (debuggee)
		 * 	@param function: The function corresponding to the symbol table  
		 */
		void fill_symbols( pid_t pid, std::string function );
		
		
		/**
		 *	Subtract the base pointer from the symbol table to get back the offsets
		 * 
		 * 	@param pid: Process ID of the child (debuggee)
		 * 	@param function: The function corresponding to the symbol table  
		 */
		void delete_symbols( pid_t pid, std::string function );
		
		
		/**
		 *	Helper to handle breakpoints
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param in_step: Whether we are stepping through our breakpoint
		 */
		void brkpt_handler( pid_t pid, bool in_step );
		
		
		/**
		 *	Inserts all the breakpoints, called after user provided 'continue' command
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void insert_brkpt_batch( pid_t pid );
		
		
		/**
		 *	Inserts all the watchpoints, called after user provided 'continue' command
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void insert_watchpt_batch( pid_t pid );
		
		
		/**
		 *	Prints out all break/watch point infomation, called when user inputs 'info' command
		 *
		 */
		void print_allpt_info();
		
		
		/**
		 *	Handler for removing watchpoints
		 *
		 * 	@param pid: Process ID of the child (debuggee)  
		 * 	@param input_cmd: The variable name encoded in a string
		 */
		void handle_rm_watch(  pid_t pid, std::string input_cmd );
		
		
		/**
		 *	Handler for setting or removing breakpoints
		 *
		 * 	@param pid: Process ID of the child (debuggee)  
		 * 	@param input_cmd: The line number / function name encoded in a string
		 * 	@param in_break: Whether we are inserting a breakpoint or not, true = inserting
		 */
		void handle_brk_or_rm( pid_t pid, std::string input_cmd, bool in_break );
		
		
		/**
		 *	Find and remove breakpoint
		 *
		 * 	@param pid: Process ID of the child (debuggee)  
		 * 	@param str: The line number / function name encoded in a string
		 * 	@param is_line_num: Whether the breakpoint is at a line number of function
		 */
		void find_print_rm_loc( pid_t pid, std::string &str, bool is_line_num );
		
		
		/**
		 *	Initial helper to remove the breakpoint
		 *
		 * 	@param pid: Process ID of the child (debuggee)  
		 * 	@param line_num: The line number we want to insert into
		 */
		void rm_brkpt_helper( pid_t pid, int line_num );
		
		
		/**
		 *	Finds the breakpoint location, used for setting breakpoints (cannot set directly at main)
		 *
		 * 	@param str: The line number / function name encoded in a string
		 * 	@param is_line_num: Whether the breakpoint is at a line number of function
		 */
		void find_print_brk_loc( std::string &str, bool is_line_num );
		
		
		/**
		 *	Initial helper to insert the breakpoint
		 *
		 * 	@param addr: The address of the line
		 * 	@param line_num: The line number we want to insert into
		 * 	@param direct_hit: If we asked for a correct line number
		 */
		void insert_brkpt_helper( void* addr, int line_num, bool direct_hit );
		
		
		/**
		 *	Confirmation function to request if the user wants to exit
		 *
		 * 	@return True if the user wants to exit
		 */
		bool confirm_exit();
		
		
		/**
		 *	Checks whether the command provided is a 'exit' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'exit' command was provided
		 */
		bool input_exit( std::string &input );
		
		
		/**
		 *	Checks whether the command provided is a 'watch' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'watch' command was provided
		 */
		bool input_watch( std::string &input );
		
		
		/**
		 *	Checks whether the command provided is a 'remove' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'remove' command was provided
		 */
		bool input_rm( std::string &input );
		
		
		/**
		 *	Checks whether the command provided is a 'print' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'print' command was provided
		 */
		bool input_print( std::string &input );
		
		
		/**
		 *	Checks whether the command provided is a 'break' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'break' command was provided
		 */
		bool input_break( std::string &input );
		
		
		/**
		 *	Checks whether the command provided is a 'next' command
		 *
		 * 	@param input: A string representing a command
		 * 	@return True if a 'next' command was provided
		 */
		bool input_next( std::string &input );
		
		
		/**
		 *	Check to see if we singlestepped to a breakpoint instruction
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return True if we are at a breakpoint
		 */
		bool is_brkpt_step( pid_t pid );


		/**
		 *	Checks whether the input is a valid line number
		 *
		 * 	@param input: A string of characters to check whether it is a valid number 
		 * 	@return True if the input is a valid number
		 */
		bool is_num( std::string &input );
		
		
		/**
		 *	Check to see if the current instruction is a breakpoint
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return True if we are at a breakpoint
		 */
		bool is_brkpt( pid_t pid );
		
		
		/**
		 *	Sets the data and instruction pointer back to its pre-breakpoint state
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param instr_ptr: The former instruction pointer address
		 * 	@param data: The data the former instruction pointer was referencing
		 */
		void handle_brkpt( pid_t pid, void* instr_ptr, void* data );
		
		
		/**
		 *	Checks if a watchpoint exist or not
		 *
		 * 	@return True if a watchpoint exists
		 */
		bool watchpt_exist();
		
		
		/**
		 *	Create a watchpoint for the symbol (variable) specified
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param symbol: The variable we want to watch 
		 */
		void set_watchpt( pid_t pid , std::string symbol );
		
		
		/**
		 *	Create a breakpoint at the address specified
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param addr: The address of the data we want to set a breapoint at
		 * 	@param is_new_brkpt: Whether this breakpoint is a new breakpoint or not
		 */
		void set_brkpt( pid_t pid, void* addr, bool is_new_brkpt );
			
		
		/**
		 *	Prints out information
		 *
		 */
		void printHelp();
		
		
		/**
		 *	Prints the intro for our pTrace-debugger
		 *
		 */
		void printIntro();
		
		
		/**
		 *	Prints all the registers which gdb prints
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void printRegisters( pid_t pid );
		
		
		/**
		 *	Gets the instruction pointer
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return The address of the instruction pointer
		 */
		void* get_instr_ptr( pid_t pid );


		/**
		 *	Sets the instruction pointer
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void set_instr_ptr( pid_t pid, void* addr );


		/**
		 *	Gets the base pointer
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return The address of the stack pointer
		 */
		void* get_base_ptr( pid_t pid );


		/**
		 *	Gets the instruction pointer
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@return The address of the stack pointer
		 */
		void* get_stack_ptr( pid_t pid );


		/**
		 *	Gets the return address
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param stack_pointer: The (current) stack pointer
		 * 	@return The return address of a function
		 */
		void* get_ret_addr( pid_t pid, void* stack_pointer );


		/**
		 *	Gets the data from the specified address
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param addr: The address of the data we want to access
		 * 	@return The data at the specified address 
		 */
		long get_data( pid_t pid, void* addr );


		/**
		 *	Sets the data at the specified address
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 * 	@param addr: The address of the data we want to access
		 * 	@param data: The data we want to set at the specified address
		 */
		void set_data( pid_t pid, void* addr, void* data );


		/**
		 *	Gets all the register values and stores it in the struct 'regs' defined globally above
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void getRegisters( pid_t pid );



	public:
		/**
		 *	The beginning of our program
		 *
		 * 	@param argc: Arguments passed straight from original main function
		 * 	@param argv: Arguments passed straight from original main function
		 * 	@return Used for exit status checking
		 */
		int main_debugger( int argc, char* argv[] );	
		

}; 


#endif
