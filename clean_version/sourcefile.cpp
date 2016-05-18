/**
 * 	@file: sourcefile.cpp
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 

#include <cassert> 
#include <fstream>

#include "sourcefile.h"
#include "helpers.h"

using std::vector;
using std::string;
using std::ifstream;


/**
 *	Constructor: fills the source vector with the contents of the file name provided
 *
 */
SourceFile::SourceFile( string file_line ) {
	getFileLines( file_line );
}


/**
 *	Parses the file line given (has to be in very specific format) to get a source file name
 *	Should be either { CU: ./filename  OR  blah/(.../)filename } 
 *	Then opens the source file and stores it in a vector
 *
 */
void SourceFile::getFileLines( string file_name ) {
	int k = 0;
	if ( (k = file_name.find("./")) != -1 )
		file_name.erase( 0, k + 2 );
	else file_name.erase( 0, file_name.find(" ") + 1 );
	
	filename = file_name.substr( 0, file_name.length() - 1 );

	ifstream source( filename );	
	assert( source.is_open() && "Cannot open source file" ); 
	
	string line;
	
	// make vector 1 indexed
	sourceFile.push_back("");				

	while ( getline(source, line) ) {
		trim( line );
		sourceFile.push_back( line );
	}

	source.close();
}


/**
 *	Returns the line in the file corresponding to the line number
 *	Asserts to make sure the line numbers are valid
 *
 */
string SourceFile::get_line( int line_num ) {
	assert( (line_num >= 0) && "Line number cannot be negative" );
	assert( (line_num < sourceFile.size()) && "Line number exceeded file length" );
	
	return sourceFile[ line_num ];
}


/**
 *	Gets the length of the sourceFile vector which holds the contents of the file
 *
 */
int SourceFile::get_file_len() {
	return sourceFile.size();
}
