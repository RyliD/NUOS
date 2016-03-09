/************************************************************************************************
*												*
*	I N C L U D E    F I L E S								*
*												*
************************************************************************************************/
/*----------------------------------------------------------------------------------------------|
|		string_functions.h								|
|----------------------------------------------------------------------------------------------*/
#include "../headers/string_functions.h"


void string_tokenize(char * source) {
	/*	Writing Tokenizing Subroutine	*/
}

long string_compare (char * p_str1_sn, char * p_str2_sn) {
    
	/*--------------------------------------------------------------------------------------|
	|	    compare strings null terminated and return TRUE if equal			|
	|--------------------------------------------------------------------------------------*/
	long 	x 	= 0;
	
	while( p_str1_sn[x] != '\0' && p_str2_sn[x] != '\0' ) {
		if( p_str1_sn[x] != p_str2_sn[x] )
			return FALSE;
		x++;
	}
	
	if ( p_str1_sn[x] != '\0' || p_str2_sn[x] != '\0' )
		return FALSE;
	else
		return TRUE;
}

long string_compare (char * p_str1_s, char * p_str2_s, long p_length_l) {
    
	/*--------------------------------------------------------------------------------------|
	|	    compare strings and return TRUE if equal					|
	|--------------------------------------------------------------------------------------*/
	long 	x 	= 0;
	
	while( x < p_length_l ) {
		if( p_str1_s[x] != p_str2_s[x] )
			return FALSE;
		x++;
	}
	return TRUE;
}

long string_size (char * p_str1_sn) {
	
	long 	x 	= 0;
	
	while ( p_str1_sn[x] != '\0' ) {
		x++;
	}
	return x;
}

void string_copy (char * p_source_sn, char * p_destination_sn) {
	
	/*--------------------------------------------------------------------------------------|
	|		Copy Content of One String to other -- Null Terminated			|
	|--------------------------------------------------------------------------------------*/
	long 	x 	= 0;
	
	while( p_source_sn[x] != '\0' ) {
		p_destination_sn[x] = p_source_sn[x];	
		x++;
	}
}

void string_copy (char * p_source_s, char * p_destination_s, long p_length_l) {
	
	/*--------------------------------------------------------------------------------------|
	|		Copy Content of One String to Second					|
	|--------------------------------------------------------------------------------------*/
	long 	x 	= 0;
	
	while( x < p_length_l ) {
		p_destination_s[x] = p_source_s[x];	
		x++;
	}
}

long string_contains_c (char * p_str1_s, char p_str2_c, long p_length_l) {
    
	/*--------------------------------------------------------------------------------------|
	|	    Check if a string contains specific character				|
	|--------------------------------------------------------------------------------------*/
	long 	x 	= 0;
	
	while ( x < p_length_l ) {
		if ( p_str1_s[x] == p_str2_c ) {
			return TRUE;	
		}
		x++;
	}
	return FALSE;
}

void enlarge_array(char* p_source_s) {
	
	/*--------------------------------------------------------------------------------------|
	|	    double the size of the array				|
	|--------------------------------------------------------------------------------------*/
	size_t size_of_string = sizeof(p_source_s) / sizeof(p_source_s[0]);
	char * enlarged_array = char[size_of_string * 2];
	string_copy(p_source_s, enlarged_array, size_of_string);
	p_source_s = enlarged_array;
}
