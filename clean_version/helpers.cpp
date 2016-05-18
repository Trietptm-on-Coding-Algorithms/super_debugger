/**
 * 	@file: helpers.cpp
 * 	@author: Guiping Xie 
 *
 * 	@description: C++ helper functions
 *	@date: Spring 2016
 *
 */
 
#include <algorithm> 
 
#include "helpers.h" 

using std::string;
using std::not1;
using std::ptr_fun;
 
/**
 *	Trim from start / left (in place)
 */
void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
}


/**
 *	Trim from end / right (in place)
 */
void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
}


/**
 *	Trim both left and right (in place)
 */
void trim(string &s) {
    ltrim(s);
    rtrim(s);
}


/**
 *	Trim from start / left (copying)
 */
string ltrimmed(string s) {
    ltrim(s);
    return s;
}


/**
 *	Trim from end / right (copying)
 */
string rtrimmed(string s) {
    rtrim(s);
    return s;
}


/**
 *	Trim both left and right (copying)
 */
string trimmed(string s) {
    trim(s);
    return s;
}


/**
 *	Converts paramter string to lowercase 
 *
 */
void str_to_lower( string &str ) {
	transform( str.begin(), str.end(), str.begin(), ::tolower);
}


/**
 *	Converts paramter string to lowercase (copying)
 *
 */
string str_to_lowercp( string str ) {
	transform( str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

 
