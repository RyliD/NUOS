// Parsing commands and texts of the input, tokenize and figure out what to do with it.

#define CURRENT_STATE = 'A'

struct instruction {
	char[] instruction_string;
	int instruciton_index;
};

// take in a stream of characters
void take_stream(char[] string) {
    
    size_t size_of_string = sizeof(string) / sizeof(string[0])
    int index = 0;
    while(index < size_of_string)
	{
		char current = string[index];
		switch(current)
		{
			case 'a':
				if(CURRENT_STATE == 'A')
				{
					go to state as needed
				}
				else if...
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
			case 'z':
			case '0':
			case '1':
			case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
			case '9':
			case '-':
			//any other special character
		}
	}
};

void try_parse_instruction(instruction ins)
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
