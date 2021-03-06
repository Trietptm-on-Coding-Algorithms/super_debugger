/**
 * 	@file: allfunct.cpp
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 

#include <cassert>
 
#include "allfunct.h"
#include "functdata.h"
#include "helpers.h"

using std::string;
using std::vector;
using std::map;

/**
 *	Creates the symbol and inserts it into the map
 *
 */
bool AllFunct::get_type( string line, symbol_data &symbol, map<string, symbol_data> &symbol_table  ) {
	int idx = -1;
	int j_idx = -1;
	bool flag = false;
	
	for ( int i = 0; i < 14 /* manual entry */ ; ++i ) {
		for ( int j = 0; j < accept_types[i].size(); ++j ){ 
			if ( line.find(accept_types[i][j]) != -1 ) {
				idx = i;
				j_idx = j;
				flag = true;
				break;
			}
		}
		
		if ( flag )
			break;
	}

	if ( idx == -1 )
		return false;
		
	symbol.type = idx;	

	string name = line.substr( 0, line.find("=") );
	name.erase( 0, line.find(accept_types[idx][j_idx]) + accept_types[idx][j_idx].length() );
	trim( name );
	
	if ( symbol_table.find(name) == symbol_table.end() ) 
		symbol_table[name] = symbol;
	
	return true;
}


/**
 *	Parse the assembly code lines 
 * 	
 */
ObjDump::individ_x86 AllFunct::parseStr( string code ) {
	individ_x86 parsedx86;
	int k = 0;

	string addr = code.substr( 0, (k = code.find(':')) );
	trim( addr );
	long mem_addr = stol( addr, NULL, 16 ); 			// in hex so we get a memory address
	parsedx86.addr = (void*)mem_addr;
	
	string data;
	int i;
	for (	i = k + 1; i < code.length(); ++i ) 
		if ( code[i] != '\t' )
			break;
	
	for ( ; i < code.length(); ++i ) {
		if ( code[i] != '\t' )
			data += code[i];
		else break;
	}

	trim( data );
	parsedx86.instr_code = data;
	
	string instr;
	
	for ( ; i < code.length(); ++i )
		instr += code[i];
	
	trim( instr );
	parsedx86.read_instr_code = instr;
	
	return parsedx86;
}


/**
 *	Fill the symbol vector with all declared varaiables
 *
 */
void AllFunct::fillSymbols( string function ) {	
	for ( int i = 0; i < ( (all_functs[ function ]).x86_code ).size(); ++i ) {
		x86 temp = ( (all_functs[ function ]).x86_code )[i];
		vector< individ_x86 > line_asm = temp.assembly;
		
		// look at the individual parts for the assembly code
		for ( int j = 0; j < line_asm.size(); ++j ) {
			string asm_line = line_asm[j].read_instr_code;
			
			if ( asm_line.find("(%rbp)") != -1 && asm_line.find("(%rbp)") != 0 && asm_line.find("(%rbp),") == -1 ) {
				asm_line.erase( 0, asm_line.find(",") + 1 );	
				long offset = stol( asm_line, NULL, 16 );
				string line = sourceFile[ temp.line ];				// the line in the source file
				
				symbol_data new_symbol;
				new_symbol.addr = offset;

				// assuming only 1 line of code per line
				// can have type declaration before initialization --- need to handle two cases
				// only handling stack and text data for now --- no malloc / heap
				// char* must be char* not char *
				if ( !get_type(line, new_symbol, (all_functs[ function ]).symbol_table) ) {				// only handling the case where everything is initialized in one line
					// TO DO
					
					// if we cannot find the variable name type
					//cerr << "Cannot find type - view 'help' for a list of accepted types\n";
				}
			} 
		}
	}
}


/**
 *	Fills the 'all_functs' map with functions to function data
 *
 */
void AllFunct::parse_funct_map( map< string, vector<string> > &functions ) {
	for ( auto it = functions.begin(); it != functions.end(); ++it ) {
		FunctData info;
		
		vector< string > assembly = it -> second;		
		int len = assembly.size();
		int i = 0;
		
		while ( i < len ) {
			x86 temp;
			
			temp.line = stoi( assembly[i].substr(assembly[i].find(":") + 1) );
			++i;
			
			while ( i < len && assembly[i][0] == ' ' ) {
				(temp.assembly).push_back( parseStr(assembly[i]) );
				++i;
			}
			
			info.set_x86( temp );
		}
		
		assert( !info.get_x86size() && "Assembly vector is empty" );

		// get last addr of initialization of the function (to get the base pointer addr)
		x86 first = (info.get_x86())[0];
		vector< individ_x86 > get_last = first.assembly;
		info.set_baseaddr( get_last[ get_last.size() - 1 ].addr );
		
		// get line number the function starts at
		info.set_startline( first.line );
		
		// get last line number
		x86 last = (info.get_x86())[ info.get_x86size() - 1 ];
		info.set_endline( last.line );
		
		// we haven't filled the symbol table yet
		info.set_sym( false );
		
		assert( (all_functs.find(it -> first) == all_functs.end()) && "Duplicate function names" );
		all_functs[ it -> first ] = info;				// add to function map
		
		map< string, symbol_data > symbol_table;
		info.set_symtable( symbol_table );
		fillSymbols( it -> first );
	}
}
