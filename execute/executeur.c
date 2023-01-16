#include "executeur.h"

/**
   @brief run the code VM[cfa] in a recursive way
   @param int cfa
 */
void runCodecfa(int cfa){
    //if (readFlg) {
    //    Stack_push(&data_stack, VM[cfa]);
    //    printf("\nWe execute VM[%d] and push %d to stack.\n", cfa, VM[cfa]);
    //    cfa += 1;
    //    readFlg = 0;
    //}
    int executeVM = VM[cfa];   //executeVM maybe a cfa of a function or it is already a base function
    Stack_push(&return_stack, cfa);
    printf("\nNOW we start to execute the VM[%d]\n", cfa);
    int res;
    if (executeVM == -1) //if it is a base function, we run the function and then we pop
    {
        processeur[VM[cfa+1]]();
        myfin(&res);
        //Stack_pop(&return_stack, &res);
        printf("\nBase function: We have executed the VM[%d]\n", res);
    }
    else // if it is a LAC function, we run the code until we reach the fin
    {
        while (executeVM != cfafin) {
            if (strFlg) {
                int strLen = VM[cfa];
                //printf("\nHere comes a string with the length: %d\n", strLen);
            
                //printf("We print the string:\n");
                //for (int i = 0; i < strLen + 1; i++) {
                //    printf("%c",(char)VM[cfa+i]);
                //}

                //printf("\nthe address is %d\n", cfa);
                
                Stack_push(&data_stack, cfa); //string address in the VM

                //Stack_push(&data_stack, strLen); //Length in the VM

                cfa += (strLen+1);
                strFlg = 0; 
                executeVM = VM[cfa];
            }
            else {
                runCodecfa(executeVM);
                cfa++;
                if (readFlg) {
                    Stack_push(&data_stack, VM[cfa]);
                    printf("\nWe execute VM[%d] and push %d to stack.\n", cfa, VM[cfa]);
                    cfa += 1;
                    executeVM = VM[cfa];
                    readFlg = 0;
                }
                else {
                   executeVM = VM[cfa]; 
                }
                
            }
            
        }
        if (executeVM == cfafin) //if we reach the fin
        {
            myfin(&res);
            printf("\nLAC function: We have executed the VM[%d]\n", res);
        }
    }

};

/**
   @brief execute the code
   @param FILE* f, queue* q
 */
void execute(FILE *file, queue* q) {
    printf("\n-----Start executing-----\n");
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
        //printf("%c", ch);
        buffer[i] = ch;
    }
    //end reading to buffer

    //init the flags to false
    compileFLg = 0; 
    strFlg = 0;
    readFlg = 0;


    //find the code to execute
    lexique lex;
    q_node *temp = q->front;
    //printf("qsize is %d\n", q->size);
    for (int i = 0; i < q->size; i++){
        lex = *(lexique* )temp->element;
     
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            char ch = buffer[lex.start + i];
         
        }
        int output_size = (lex.end - lex.start) + 2;
        char output[output_size];
        
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            output[i] = buffer[lex.start + i];
            //printf("%c ", output[i]);
        }
        //printf("\n");
        output[output_size-1] = '\0';
        int cfaTemp, num;
        
        //output the result
        switch (lex.type)
        {
        case INT:
            //printf("\n\nNumber!!!!!!!!!!!!!!!!!!!!\n\n");
            num = atoi(output);
            Stack_push(&data_stack, num);
            printf("We read a INT and push to data stack: %d\n", num);
            break;
        case MOTS:
            //int cfaTemp;
            cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
            printf("We read a MOTS: %s and find the function in %d\n", output, cfaTemp);
            runCodecfa(cfaTemp);
            break;
        case STRING:
            
            
            break;

        default:
            break;
        }
        temp = temp->next;
    }
    printf("\n-----End executing-----\n\n");


};


