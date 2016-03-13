// Parsing commands and texts of the input, tokenize and figure out what to do with it.

#include "../headers/tokens.h"
#include "../headers/string_fuctions.h"

struct instruction {
	char[] instruction_string;
	int instruciton_index;
};

params_token parse_param(char[] string) {
	size_t size_of_string = sizeof(string) / sizeof(string[0]);//size of input
	params_token tokens = new params_token();//the token to be returned
	int index_of_input = 0;
	int index_of_token_array = 0;
	int index_of_current_param = 0;
    while(index_of_input < size_of_string)//while we have characters left
	{
		if((index_of_current_param - 3) < string_size(tokens->params_array[index_of_token_array]))//if the array is almost full resize
		{
			enlarge_array(tokens->params_array[index_of_token_array]);
		}
		char current = string[index_of_input];
		if(current == '-') {//new param
		//these if statements are seperate because if the first one is successful we don't want to run the else on like 31.
			if(index_of_current_param > 0) {//this is here so that 2 - params don't leave an empty spot in the array.
				index_of_current_param = 0;
				index_of_token_array++;
			}
		}
		else {
			//put the character in the array
			tokens->params_array[index_of_token_array][index_of_current_param] = current;
			index_of_current_param++;
		}
	}
	//possible todo, go through tokens and figure out which methods to call.
	return tokens;
}

instruction_token parse_instruction(char[] string) {
    
    size_t size_of_string = sizeof(string) / sizeof(string[0]);//size of input
	instruction_token tokens = new instruction_token();//the token to be returned
	int index_of_input = 0;
	int index_of_token_array = 0;
    while(index_of_input < size_of_string)//while we have characters left
	{
		if((index_of_token_array - 3) < string_size(tokens->instruction_string)//if the array is almost full resize
		{
			enlarge_array(tokens->instruction_string);
		}
		char current = string[index_of_input];
		if(current == '-') {//end of command, this is a param
			//todo, determine which command it is and add appropriate method to call.
			return token;
		}
		else {
			//put the character in the token
			tokens->instruction_string[index_of_token_array] = current;
			index_of_token_array++;
		}
	}
	//todo, determine which command it is and add appropriate method to call.
	return token;
};

/*void try_parse_instruction(instruction ins)
{
	go through and try to parse sections;
	try_parse_command(ins);
	try_parse_param(ins);
	take the tokens and interpret instruction
};

void try_parse_command(instruction ins)
{
	try to parse a command and create token;
};

void try_parse_param(instruction ins)
{
	try to parse 1 or more param and create token
};
*/