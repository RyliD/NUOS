// Parsing commands and texts of the input, tokenize and figure out what to do with it.

#define CURRENT_STATE = 'A'

// take in a stream of characters
void take_stream(char[] string) {
    
    size_t sizeOfString = sizeof(string) / sizeof(string[0])
    
    while(true) {
        switch(string) {
        case 'c':
            if(CURRENT_STATE == 'C')
                
        case 'd':
            printf("does the thing");
            break;
        }    
    }
    
};
