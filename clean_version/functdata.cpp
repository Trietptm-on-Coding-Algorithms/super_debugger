/**
 * 	@file: functdata.cpp
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 

#include <cassert>
 
#include "functdata.h"



/* Returns the line number the function starts at */
int FunctData::get_startline() { return start_line; }


/* Returns the line number the function ends at */
int FunctData::get_endline() { return end_line; }


/* Returns whether the symbol table was filled (added base pointer) or not */
bool FunctData::get_sym() { return symbol_filled; }


/* Returns the base pointer of the function */
void* FunctData::get_baseptr() { return base_ptr_addr; }


/* Returns the last valid address of this function */
void* FunctData::get_baseaddr() { return get_base_addr; }


/* Returns a vector of the assembly code as a reference */
std::vector< ObjDump::x86 >& FunctData::get_x86() { return x86_code; }


/* Returns the symbol table corresponding to the function as a reference */
std::map< std::string, ObjDump::symbol_data >& FunctData::get_symtable() { return symbol_table; }

/* Returns the size of the x86 vector */
int FunctData::get_x86size() { return x86_code.size(); }


/* Sets the line number the function starts at */
void FunctData::set_startline( int start_line ) { start_line = start_line; }


/* Sets the line number the function ends at */
void FunctData::set_endline( int end_line ) { end_line = end_line; }


/* Sets whether the symbol table is currently correct (added base pointer / active) */
void FunctData::set_sym( bool symbol_filled ) { symbol_filled = symbol_filled; }


/* Sets the base pointer of the function */
void FunctData::set_baseptr( void* base_ptr ) { base_ptr_addr = base_ptr; }


/* Sets the last valid address of this function */
void FunctData::set_baseaddr( void* last_addr ) { get_base_addr = last_addr; }


/* Inserts into the x86 assembly vector */
void FunctData::set_x86( ObjDump::x86 code ) { x86_code.push_back( code ); }


/*	Sets the symbol table corresponding to the function as a reference */
void FunctData::set_symtable( std::map< std::string, ObjDump::symbol_data > symbol_table ) { symbol_table = symbol_table; }



