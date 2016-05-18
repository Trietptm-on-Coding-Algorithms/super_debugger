/**
 * 	@file: allfunct.h
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 
 
#ifndef ALLFUNCT_H 
#define ALLFUNCT_H 


#include "objdump.h"

class FunctData;


class AllFunct : public ObjDump {
	private:
		/* map of functions to data --- name of function, function data */
		std::map< std::string, FunctData > all_functs;	
	
		/**
		 *	Fills the 'all_functs' map with functions to function data
		 *
		 * 	@param functions: The map of valid functions and assembly code
		 */
		void parse_funct_map( std::map< std::string, std::vector<std::string> > &functions);	
	
	
		/**
		 *	Fill the symbol vector with all declared varaiables
		 *
		 * 	@param function: The function corresponding to the symbol table
		 */
		void fillSymbols( std::string function );
		
		
		/**
		 *	Parse the assembly code lines 
		 *
		 * 	@param code: The assembly code line (string) we want to parse
		 * 	@return An individ_x86 object holding the parsed contents
		 */
		individ_x86 parseStr( std::string code );
	

		/**
		 *	Creates the symbol and inserts it into the map
		 *
		 * 	@param line: The source code line
		 * 	@param symbol: The symbol_data object we want to fill
		 * 	@param symbol_table: The symbol table of the function
		 * 	@return True if we can find the type of the symbol (variable)
		 */
		bool get_type( std::string line, symbol_data &symbol, std::map< std::string, symbol_data > &symbol_table );
		
			
	public:
		
		AllFunct( std::map< std::string, std::vector<std::string> > &functions );
		
};

#endif
