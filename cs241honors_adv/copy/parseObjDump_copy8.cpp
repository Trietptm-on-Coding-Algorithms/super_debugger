/**
 * 	@file: objDump
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

using namespace std;

struct symbol_data {
	long addr;					// makes it easier to add a long to a void*
	int type;
};

struct individ_x86 {
	void* addr;
	string instr_code;
	string read_instr_code;
};

struct x86 {
	int line;
  vector< individ_x86 > assembly;
};

struct funct_data {
	void* base_ptr_addr;
	vector< x86 > x86_code;
	map< string, symbol_data > symbol_table;		// symbol, symbol data
};

// mappers from line to addr and addr to line
map< int, void* > line_to_addr;
map< void*, int > addr_to_line;

//vector< string > mainFunct;							// only debugging main for now
vector< string > sourceFile;

// the file name
string filename;

// map of functions to data
map< string, funct_data > all_functs;			// name of function, function data

// list of accepted types
static vector< string > accept_types[14];

static int sizeof_types[] = { sizeof(unsigned int), sizeof(unsigned long long), 
sizeof(unsigned long), sizeof(long long), sizeof(int), sizeof(long), sizeof(long double), 
sizeof(double), sizeof(float), sizeof(unsigned short), sizeof(short), sizeof(char) };

// Got these online - http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

/**
 *	Trim from start / left (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
}


/**
 *	Trim from end / right (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
}


/**
 *	Trim both left and right (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}


/**
 *	Trim from start / left (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string ltrimmed(string s) {
    ltrim(s);
    return s;
}


/**
 *	Trim from end / right (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string rtrimmed(string s) {
    rtrim(s);
    return s;
}


/**
 *	Trim both left and right (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string trimmed(string s) {
    trim(s);
    return s;
}


// ------ END ------


/**
 *	Fills the acceptable type array 
 *
 */
void fillTypeArr() {
	static vector< string > u_int_arr = {"unsigned int "};
	static vector< string > u_ll_arr = {"unsigned long long int ", "unsigned long long "};
	static vector< string > u_l_arr = {"unsigned long int ", "unsigned long "};
	static vector< string > ll_arr = {"signed long long int ", "long long int ", "signed long long ", "long long "};
	static vector< string > int_arr = {"signed int ", "int "};
	static vector< string > l_arr = {"signed long int ", "signed long ", "long int ", "long "};
	static vector< string > ld_arr = {"long double "};
	static vector< string > d_arr = {"double "};
	static vector< string > f_arr = {"float "};
	static vector< string > u_s_arr = {"unsigned short int ", "unsigned short "};
	static vector< string > s_arr = {"signed short int ", "signed short ", "short int ", "short "};
	static vector< string > c_arr = {"char "};
	static vector< string > cp_arr = {"char* "};
	static vector< string > str_arr = {"string "};
	
	accept_types[0] = u_int_arr; 
	accept_types[1] = u_ll_arr;
	accept_types[2] = u_l_arr;
	accept_types[3] = ll_arr;
	accept_types[4] = int_arr;
	accept_types[5] = l_arr;
	accept_types[6] = ld_arr;
	accept_types[7] = d_arr;
	accept_types[8] = f_arr;
	accept_types[9] = u_s_arr;
	accept_types[10] = s_arr;
	accept_types[11] = c_arr;
	accept_types[12] = cp_arr;
	accept_types[13] = str_arr;
}

/**
 *	Prints the parsed objdump file (assembly code)
 *
 */
void printData( vector< x86 > &x86_code ) {
	for ( int i = 0; i < x86_code.size(); ++i ) {
		cerr << "--------------------------------------------------------------------------------\n\n";
		cerr << "Line number in " << filename << " is: " << x86_code[i].line << "\n";
		cerr << "Line is: \"" << sourceFile[ x86_code[i].line ] << "\"\n";
		
		cerr << "Assembly code is:\n";
		vector< individ_x86 > temp = x86_code[i].assembly;
		for ( int j = 0; j < temp.size(); ++j ) {
			cerr << "  Parsed Output:\n";
			cerr << "    Memory address is: " << temp[j].addr << "\n";
			cerr << "    Instruction code is: " << temp[j].instr_code << "\n";
			cerr << "    Instr in x86 readable format is: " << temp[j].read_instr_code << "\n";
		}
		
		cerr << "\n";
	}
}


/**
 *	Prints the symbols
 *
 */
void printSymbols( map< string, symbol_data > &symbol_table ) {
	for ( auto it = symbol_table.begin(); it != symbol_table.end(); ++it ) {
		symbol_data temp = it -> second;
		cerr << it -> first << "  " << temp.addr << "  " << accept_types[temp.type][0] << "\n";
	}
}

 
/**
 *	Prints the mappers from address to lines and lines to addresses
 *
 */
void printMaps() {
	cerr << "Lines to memory addresses\n";
	for ( auto it = line_to_addr.begin(); it != line_to_addr.end(); ++it ) 
		cerr << it -> first << "\t" << it -> second << "\n";
	cerr << "\n";
	
	cerr << "Memory addresses to lines\n";
	for ( auto it = addr_to_line.begin(); it != addr_to_line.end(); ++it ) 
		cerr << it -> first << "\t" << it -> second << "\n";
	cerr << "\n";
}


/**
 *	Fill the mappers from address to lines and lines to addresses
 *
 */
void fill_line_addr( vector< string > &decoded ) {
	for ( int i = 7; i < decoded.size(); ++i ) {
		if ( decoded[i].empty() )
			break;
			
		stringstream ss;
		int line;
		string addr, file;
		ss << decoded[i];
		ss >> file >> line >> addr;
		
		long mem_addr = stol( addr, NULL, 16 );				// convert to void pointer
		
		if ( line_to_addr.find(line) == line_to_addr.end() ) 
			line_to_addr[line] = (void*)mem_addr;

		addr_to_line[(void*)mem_addr] = line; 	
	}
}


/**
 *	Creates the symbol and inserts it into the map
 *
 * 	@param line: The source code line
 * 	@param symbol: The symbol_data object we want to fill
 * 	@return True if we can find the type of the symbol (variable)
 */
bool get_type( string line, symbol_data &symbol, map<string, symbol_data> &symbol_table  ) {
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
 *	Fill the symbol vector with all declared varaiables
 *
 * 	@param function: The function corresponding to the symbol table
 */
void fillSymbols( string function ) {	
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
 *	Opens the object dump file and stores it in a vector
 *
 * 	@param file_name: The name of the objdump file
 * 	@return True if the objdump file cannot be opened
 */
 /*
bool getObjDump( string file_name ) {
	ifstream parseMe( file_name );				// got from online - cppreference
	if ( parseMe.is_open() ) {
		string line;

		while ( getline(parseMe, line) ) {
			if ( line.find("<main>:") != -1 ) {
				object_dump.push_back( line );
				break;
			}
		}
		
		while ( getline(parseMe, line) ) {
			if ( !line.empty() )
				object_dump.push_back( line );
			else break;
		}

		parseMe.close();
	}
	else {
		cerr << "\n\t\e[1mObject dump file could not be opened\e[0m\n\n";
		return true;
	}
	
	return false;
}
*/

/**
 *	Opens the source file and stores it in a vector
 *
 * 	@param file_name: The absolute path of the source file
 * 	@return True if the source file cannot be opened
 */
bool getFileLines() {
	int k = 0;
	if ( (k = filename.find("./")) != -1 )
		filename.erase( 0, k + 2 );
	else filename.erase( 0, filename.find(" ") + 1 );
	
	filename = filename.substr( 0, filename.length() - 1 );

	ifstream source( filename );	
	if ( source.is_open() ) {
		string line;
		sourceFile.push_back("");

		while ( getline(source, line) ) {
			trim( line );
			sourceFile.push_back( line );
		}

		source.close();
	}
	else {
		cerr << "\n\t\e[1mYour file --- " << filename << " --- could not be opened\e[0m\n\n";
		return true;
	}
	
	return false;
}


/**
 *	Parses the absolute location of the file to get the file name
 *
 * 	@param fileloc: The absolute path of the file location 
 */
 /*
void getFileName( string fileloc ) {
	int idx = 0;

	for ( int i = fileloc.length() - 1; i >= 0; --i ) {
		if ( fileloc[i] == '/' ) {
			idx = i;
			break;
		}
	}

	filename = fileloc.substr( idx + 1 );
}


/**
 *	Parse the assembly code lines 
 *
 * 	@param code: The assembly code line (string) we want to parse
 * 	@return An individ_x86 object holding the parsed contents
 */
individ_x86 parseStr( string code ) {
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
 *	Parses the whole assembly file
 *
 * 	@param indices: The indices of the assembly file (broken by line numbers)
 * 	@param linenumber: The line number of source file corresponding to the assembly code
 */
 /*
void parseAssem( const vector<int>& indices, const vector<int>& linenumber ) {
	int i = 0;
	
	while ( i < indices.size() - 1 ) {
		x86 temp;	
		int k = indices[i];
		int e = indices[i + 1];
		
		while ( k < e ) {
			temp.assembly.push_back( parseStr(mainFunct[k]) );
			++k;
		}
		
		++i;
		x86_code.push_back( temp );
	}
	
	x86 temp;	
	int k = indices[i];
	
	while ( k < mainFunct.size() ) {
		temp.assembly.push_back( parseStr(mainFunct[k]) );
		++k;
	}
	
	x86_code.push_back( temp );
}


/**
 *	Fills the 'all_functs' map with functions to function data
 *
 * 	@param functions: The map of valid functions and assembly code
 */
void parse_funct_map( map< string, vector<string> > &functions ) {
	for ( auto it = functions.begin(); it != functions.end(); ++it ) {
		funct_data info;
		
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
			
			(info.x86_code).push_back( temp );
		}
		
		assert( !(info.x86_code).empty() && "Assembly vector is empty" );
		x86 first = (info.x86_code)[0];
		vector< individ_x86 > get_last = first.assembly;
		info.base_ptr_addr = get_last[ get_last.size() - 1 ].addr;
		
		assert( (all_functs.find(it -> first) == all_functs.end()) && "Duplicate function names" );
		all_functs[ it -> first ] = info;				// add to function map
		
		map< string, symbol_data > symbol_table;
		info.symbol_table = symbol_table;
		fillSymbols( it -> first );
	}
}


/**
 *	Fills the 'all_functs' map with functions to function data
 *
 * 	@param objdump: The objdump file
 * 	@param functions: The list of valid functions
 * 	@param demangled: The demangled list of valid functions 
 */
void fill_funct_map( vector<string> &objdump, vector<string> &functions, vector<string> &demangled ) {
	int len = objdump.size();
	int i = 0;
	int idx;
	map< string, vector<string> > all_funct_asm;
	while ( i < len && !functions.empty() ) {
		idx = -1;
		for ( int j = 0; j < functions.size(); ++j ) {
			if ( objdump[i].find( "<" + functions[j] + ">:" ) != -1 ) {
				idx = j;
				functions.erase( functions.begin() + j );
				break;
			}
		}
		
		// if true, this is an individual function
		if ( idx != -1 ) {
			i += 2;
			vector< string > funct_asm;
			while ( !objdump[i].empty() ) {
				funct_asm.push_back( objdump[i] );
				++i;
			}
			
			assert( (all_funct_asm.find(demangled[idx]) == all_funct_asm.end()) && "Duplicate function names" );
			all_funct_asm[ demangled[idx] ] = funct_asm;
		}
		
		++i;
	}
	
	parse_funct_map( all_funct_asm );
}


/**
 *	Gets all the valid function names in the program
 *
 * 	@param symbol_lines: The symbol file
 * 	@return A list of all the valid functions in the program
 */
vector<string> parse_symbols( vector<string> &symbol_lines ) {
	// used for stringstream
	string addr, type, name;
	vector< string > funct_names;
	for ( int i = 0; i < symbol_lines.size(); ++i ) {
		if ( symbol_lines[i].find(filename) != -1 ) {
			stringstream ss;
			ss << symbol_lines[i];
			ss >> addr >> type >> name;
			
			if ( !type.compare("T") )
				funct_names.push_back( name );
		}
	}
	
	return funct_names;
}


/**
 *	Helper to fill the destination vector with the file contents
 *
 * 	@param ptr: A file pointer containing the content we want to copy
 * 	@param dest: The vector we want to store the contents with
 */
void fill_vector_temp( FILE* ptr, vector<string> &dest ) {
	rewind( ptr );
	char* line = NULL;
	size_t n = 0;
	while ( getline(&line, &n, ptr) != -1 ) {
		line[ strlen(line) - 1 ] = 0;
		dest.push_back( line );
	}

	free( line );
	fclose( ptr );
}


/**
 *	Helper to wait for the child process
 *
 * 	@param pid: Process ID of the child (debuggee) 
 */
void wait_helper( pid_t pid ) {
	int status;
	int k = waitpid( pid, &status, 0 );			
	
	assert( (k != -1) && "Child process for object dump failed" ); 
}


/**
 *	Helper to redirect stdout and close the file descriptor
 *
 * 	@param ptr: A file pointer we will redirect stdout to
 */
void redirect_close_fd( FILE* ptr ) {
	int fd = fileno( ptr );
		
	// make stdout go to file	
	assert( (dup2(fd, 1) != -1) && "Could not redirect stdout to our file for objdump pipe" );
	
	// fd no longer needed - the dup'ed handles are sufficient
	assert( !close(fd) && "Could not close file descriptor for objdump" );
}


/**
 *	Helper for the child process
 *
 * 	@param ptr: A file pointer we will redirect stdout to
 * 	@param exec_arr: The array containing the program we want to execute
 */
void child_helper( FILE* ptr, const char** exec_arr ) {
	redirect_close_fd( ptr );

	int k = execvp( exec_arr[0], (char* const*)exec_arr );
	assert( (k != -1) && "Execution for object dump failed" );
}


/**
 *	Demangles the all the function names --- only really needed for C++
 *
 * 	@param funct_names: The function names
 * 	@return The list of demangled function names
 */
vector<string> get_demangled( vector<string> &funct_names ) {
	FILE* demangled_name = tmpfile();
	assert( demangled_name && "Temp file provided was NULL" ); 
	
	pid_t filter = fork();
	assert( (filter != -1) && "Forking failed for object dump process" ); 
	
	if ( !filter ) {
		redirect_close_fd( demangled_name );
		
		for ( int i = 0; i < funct_names.size(); ++i ) {
			char exec_cmd[ 16 + funct_names[i].length() ];
			strcpy( exec_cmd, "c++filt -p ");
			strncat( exec_cmd, &funct_names[i][0], funct_names[i].length() );
						
			int k = system( exec_cmd );
			assert( (k != -1) && "Execution for name demangling failed" );
		}
		
		exit( 0 );
	}

	wait_helper( filter );
	
	vector< string > demangled;
	fill_vector_temp( demangled_name, demangled );
	
	return demangled;
}


/**
 *	Run objdump with the decoded line flag
 *
 * 	@param program: The program we want to run
 */
void get_decoded_line( char* program ) {
	FILE* decoded_line = tmpfile();
	assert( decoded_line && "Temp file provided was NULL" ); 
	
	pid_t decode_objdump = fork();
	assert( (decode_objdump != -1) && "Forking failed for object dump process" ); 

	if ( !decode_objdump ) {					// in child
		const char* objdump_args[4];
		objdump_args[0] = "objdump";
		objdump_args[1]	= "--dwarf=decodedline";
		objdump_args[2]	= program;
		objdump_args[3] = NULL;
		
		child_helper( decoded_line, objdump_args );
	}
	
	wait_helper( decode_objdump );
	
	vector< string > obj_decode_lines;
	fill_vector_temp( decoded_line, obj_decode_lines );

	filename = obj_decode_lines[5];
	assert( !getFileLines() );
	
	fill_line_addr( obj_decode_lines );
}


/**
 *	Get the complete list of symbols from the program
 *
 * 	@param program: The program we want to run
 * 	@return A list of all the valid functions in the program
 */
vector<string> get_symbol_dump( char* program ) {
	FILE* symbol_dump = tmpfile();
	assert( symbol_dump && "Temp file provided was NULL" ); 
	
	pid_t symbol = fork();	
	assert( (symbol != -1) && "Forking failed for object dump process" ); 

	if ( !symbol ) {					// in child
		const char* symbol_args[3];
		symbol_args[0] = "nm";
		symbol_args[1] = "-l";
		symbol_args[2] = program;
		symbol_args[3] = NULL;
		
		child_helper( symbol_dump, symbol_args );
	}
	
	wait_helper( symbol ); 
	
	vector< string > symbol_lines;
	fill_vector_temp( symbol_dump, symbol_lines );
	
	return parse_symbols( symbol_lines );
}


/**
 *	Get the complete object dump of the program
 *
 * 	@param program: The program we want to run
 * 	@return The complete objdump as a vector
 */
vector<string> get_complete_objdump( char* program ) {
	FILE* complete_objdump = tmpfile();
	assert( complete_objdump && "Temp file provided was NULL" ); 
	
	pid_t objdump = fork();	
	assert( (objdump != -1) && "Forking failed for object dump process" ); 

	if ( !objdump ) {						// in child
		const char* objdump_args[5];
		objdump_args[0] = "objdump";
		objdump_args[1]	= "-d";
		objdump_args[2]	= "-l";
		objdump_args[3]	= program;
		objdump_args[4] = NULL; 

		child_helper( complete_objdump, objdump_args );
	}

	wait_helper( objdump );
	
	vector< string > object_dump;
	fill_vector_temp( complete_objdump, object_dump );

	return object_dump;
}


/**
 *	The beginning of our program
 *
 * 	@param argc: Arguments passed straight from original main function
 * 	@param argv: Arguments passed straight from original main function
 * 	@return Used for exit status checking
 */
int execObjDump( int argc, char* argv[] ) {
	// fills the global sccept_types array	
	fillTypeArr();
		
	// decoded line object dump
	get_decoded_line( argv[1] );

	// symbol dump --- for a list of symbols
	vector< string > funct_names = get_symbol_dump( argv[1] );	
	
	// object dump with lines
	vector< string > object_dump = get_complete_objdump( argv[1] );
	
	// gets the demangled names of the functions --- in case they do C++
	vector< string > demangled = get_demangled( funct_names );
	
	// this will do most of the parsing, fills up all the data from objdump
	fill_funct_map( object_dump, funct_names, demangled );

	//printMaps();

	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {
		cout << it -> first << "\n";
		funct_data info = it -> second;
		cout << info.base_ptr_addr << "\n";
		//printData( info.x86_code );
		printSymbols( info.symbol_table );
		cout << "\n";
		//map< string, symbol_data > symbol_table = info.symbol_table;
	}

	// now the vector object_dump has all the lines
	/*
	int len = object_dump.size();

	assert( len && "Object dump is empty" );
	
	int incre = 2;
	int idx = 0;
	vector< int > indices;
	vector< int > linenumber;
	string fileloc;
		
	while ( incre < len ) {
		if ( object_dump[incre][0] == ' ' ) {
			mainFunct.push_back( object_dump[incre] );
			++idx;
		}
		else {
			// this line corresponds to the next block of x86 instructions				
			string line = object_dump[incre];
			int linelen = line.length();
			int numstart = 0;
			
			for ( int i = linelen - 1; i; --i ) {
				if ( line[i] == ':' ) {
					numstart = i;
					break;
				}
			}

			int linenum = stoi( line.substr(numstart + 1) );
			linenumber.push_back( linenum );
			indices.push_back( idx );
			
			if ( !idx )
				fileloc = line.substr( 0, numstart );
		}
		
		++incre;
	}
	
	if ( fileloc.empty() ) {
		cerr << "\n\t\e[1mMake sure you compiled your program with the -g flag\e[0m\n\n";
		return 1;
	}
	
	// gets the file name
	//getFileName( fileloc );

	// parse the assembly x86 file
	parseAssem( indices, linenumber );
	
	fillTypeArr();
	
	//fillMaps();
	
	// print the data in the maps
	//printMaps();
	
	// fill the symbol vector
	fillSymbols();
	
	// print all the symbols
	//printSymbols();

	// print parsed data
	//printData();
	*/
	return 0;
}
