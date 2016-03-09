// Parsing commands and texts of the input, tokenize and figure out what to do with it.

#include "../headers/tokens.h"
#include "../headers/string_fuctions.h"

struct instruction {
	char[] instruction_string;
	int instruciton_index;
};
//this will return a array of tokens
void parse_param(char[] string) {
	size_t size_of_string = sizeof(string) / sizeof(string[0]);
	params_token tokens = new params_token();
	int index_of_input = 0;
	int index_of_token_array = 0;
	int index_of_current_param = 0;
    while(index_of_input < size_of_string)
	{
		if((index_of_current_param - 3) < string_size(tokens->params_array[index_of_token_array]))
		char current = string[index_of_input];
		if(current == '-') {
			if(index_of_current_param > 0) {
				index_of_current_param = 0;
				index_of_token_array++;
			}
		}
		else {
			tokens->params_array[index_of_token_array][index_of_current_param] = current;
			index_of_current_param++;
		}
	}
}

// take in a stream of characters
void parse_instruction(char[] string) {
    
    size_t size_of_string = sizeof(string) / sizeof(string[0]);
	instruction_token tokens = new instruction_token();
	int index_of_input = 0;
	int index_of_token_array = 0;
	int index_of_current_instruction = 0;
    while(index_of_input < size_of_string)
	{
		if((index_of_current_instruction - 3) < string_size(tokens->instruction_string[index_of_token_array]))
		char current = string[index_of_input];
		if(current == '-') {
			if(index_of_current_instruction > 0) {
				index_of_current_instruction = 0;
				index_of_token_array++;
			}
		}
		else {
			tokens->instruction_string[index_of_token_array][index_of_current_instruction] = current;
			index_of_current_instruction++;
		}
	}
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