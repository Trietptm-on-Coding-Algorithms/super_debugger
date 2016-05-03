//#include <bits/stdc++.h>

// 'ssh gxie2@sp16-cs241-105.cs.illinois.edu'

#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/stat.h>

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>

#include <assert.h>
#include <sys/prctl.h> 				// to exit child

#include "parseObjDump.cpp"
#include "tryingPtrace.cpp"

using namespace std;


/**
 *	Needs to compile with their program with the -g flag
 *	Should have a modern version of valgrind/linux installed
 *
 *	Format is ./super_debugger ./yourProgram
 *
 *	Need variable declarations to be in one line
 *		ie int sum = 0, NOT int sum, a, b ...
 *
 *	Might block in the first run - just crtl + c and try again
 *
 */ 


int main( int argc, char* argv[] ) {
	if ( argc != 2 ) {
		cerr << "\n\t\e[1mFormat is: ./super_debugger ./your_program\e[0m\n\n";
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
	execObjDump( argc, argv );
	
	// run our debugger
	main_debugger( argc, argv );
	
	return 0;
}
