/**
 * 	@file: sdb.cpp
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 *	NO WARRANTY
 * 
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

#include <cstring>  
#include <unistd.h>
#include <iostream>
 
#include "objdump.h"
#include "ptrace.h"

#include "sourcefile.h"

using std::cerr;


/**
 *	Needs to compile with their program with the -g flag
 *	Should have a modern version of valgrind/linux installed
 *
 *	Format is ./sdb ./yourProgram
 *
 *	Need variable declarations to be in one line
 *		ie int sum = 0, NOT int sum, a, b ...
 *
 *	Might block in the first run - just crtl + c and try again
 *
 */ 
int main( int argc, char* argv[] ) {
	if ( argc != 2 ) {
		cerr << "\n\t\e[1mFormat is: ./sdb ./your_program\e[0m\n\n";
		return 0;
	} 
	
	// checking for bad input
	char* executable = argv[1];
	
	if ( strlen(executable) > 1 ) {
		if ( !(executable[0] == '.' && executable[1] == '/') ) {
			cerr << "\n\t\e[1mInvalid input: " << executable << "\e[0m\n\n";
			return 0;	 
		}
		else {
			if ( access(&executable[2], F_OK) ) {
				cerr << "\n\t\e[1mExecutable: " << &executable[2] << " does not exist\e[0m\n\n";
				return 0;	 
			}
		}
	}
	else {
		cerr << "\n\t\e[1mInvalid input: '" << executable << "'\e[0m\n\n";
		return 0;
	}

	// execute and parse object dump of program
	//execObjDump( argc, argv );
	
	// run our debugger
	//main_debugger( argc, argv );
	
	SourceFile* p;
	SourceFile x("CU: ./helloworld.cpp:");
	p = &x;
	cerr << p -> get_file_len();
	
	return 0;
} 
