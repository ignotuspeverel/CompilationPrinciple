#include "executeur.h"

/**
   @brief execute the code
   @param FILE* f, queue* q
 */
void execute(FILE *file, queue* q) {
    //read file to buffer
    int bufferlen = 0;
    rewind(file);
    while(1) {    
		char ch = fgetc(file);
		if (ch == EOF) break;
		bufferlen++;  
	}
    char buffer[bufferlen];                      //create the buffer 
    rewind(file);
    int count = 0 ;
    for (int i = 0; i < bufferlen; i++) {
        char ch = fgetc(file);
        printf("%c", ch);
        buffer[i] = ch;
    }

    compileFLg = 0; 
    //compile_init();
    //for (int i = 0; i < bufferlen; i++) printf("%c", buffer[i]);
    printf("\n");


    //update VM and LAC
    lexique lex;
    q_node *temp = q->front;
    //printf("qsize is %d\n", q->size);
    for (int i = 0; i < q->size; i++){
        lex = *(lexique* )temp->element;
     
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            char ch = buffer[lex.start + i];
         
        }
        int output_size = (lex.end - lex.start) + 2;
        //printf("%d\n", output_size);

        char output[output_size];
        
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            output[i] = buffer[lex.start + i];
            //printf("%c ", output[i]);
        }
       // printf("\n");
        output[output_size-1] = '\0';
        
        //output the result
        switch (lex.type)
        {
        case INT:
            VM[vmPtr++] = cfalit;
            VM[vmPtr++] = atoi(output);
            break;
        case MOTS:
            if (strcmp(output, ":") == 0) compileFLg = 1;
            
            if (!compileFLg) 
            {
                int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                VM[vmPtr++] = cfaTemp;
                
                //if (strcmp(output, "count") == 0) {
                //    int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                //    VM[vmPtr++] = cfaTemp;

                //}
                //if (strcmp(output, "type") == 0) {
                //    int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                //    VM[vmPtr++] = cfaTemp;
                //}
            }
            else {
                if (strcmp(output, ":") == 0) compileFLg = 1;
            }
            break;
        case STRING:
            if (compileFLg) {
                VM[vmPtr++] = cfastr;
                int lenStr = output_size-4;
                VM[vmPtr++] = lenStr;
                for (int j = 0; j < lenStr; j++) 
                    VM[vmPtr++] = (int)output[j+2];
            }
            
            break;

        default:
            break;
        }
        temp = temp->next;
    }


};


