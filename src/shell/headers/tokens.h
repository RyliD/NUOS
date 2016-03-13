/************************************************************************************************
*												*
*	H E A D E R    G U A R D								*
*												*
************************************************************************************************/
#ifndef TOKENS_H_INCLUDE
#define	TOKENS_H_INCLUDE

typedef char array_of_50_char[50];

struct params_token {
	array_of_50_char * params_array;
	void (*instruction_func)(void);//needed?
};

struct instruction_token {
	char * instruction_string;
	void (*instruction_func)(void);//the pointer to the function that knows how to run the command
};
#endif