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
    //printf("\nPush into stack: %d-------------------------------- size: %d \n", cfa, Stack_length(&return_stack));
    //printf("\n In the stack: ");
    //for (int i = 1; i <= Stack_length(&return_stack); i++) {
    //    printf("%d ", *(return_stack.top - i*sizeof(ElemType)));
    //}
    //printf("\n");
    printf("\nNOW we start to execute the VM[%d]\n", cfa);
    int res, startloc, endloc;
    if (executeVM == -1) //if it is a base function, we run the function and then we pop
    {
        if ((cfa) != cfafin) 
        {
            //printf("\n------------------------------------ %d\n", cfa+1);
            processeur[VM[cfa+1]]();
            myfin(&res);
            //printf("\nPop out stack: %d-------------------------------- size: %d \n", res, Stack_length(&return_stack));
            //printf("\n In the stack: ");
            //for (int i = 1; i <= Stack_length(&return_stack); i++) {
            //    printf("%d ", *(return_stack.top - i*sizeof(ElemType)));
            //}
            //printf("\n");
            printf("\nBase function: We have executed the VM[%d]\n", res);
        }
        //else
        //{
        //    myfin(&res);
        //    printf("\n hahahahahahahahahahaLAC function: We have executed the VM[%d]\n", res);
        //}
        
        
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
                executeVM = VM[cfa];
                strFlg = 0; 
            }
            
            else {
                //cnt--;
                //printf("\ncnt:%d\n", cnt);
                //printf("\ncfa:%d\n", cfa);
                //printf("\ncfa:%d\n", executeVM);
                //if (cnt == 0) {
                //  printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");  
                //  exit(1);
                //}
                if(ifFlg == 1) {
                    //printf("\n----------cfa: %d---------\n",cfa);
                    endloc = VM[cfa] - 2;
                    startloc = ++cfa;
                    //printf("\n----------start: %d---------\n",startloc);
                    //printf("\n----------end: %d---------\n",endloc);
                    executeVM = VM[cfa];
                    ifFlg = 0;
                    inIf = 1;
                    ifLen = endloc - startloc + 1;
                    //printf("\n----------if len: %d---------\n", ifLen);
                }

                if(elseFlg == 1)  {
                    startloc =  VM[cfa];
                    //printf("\nthe address is %d\n", startloc);
                    endloc = VM[startloc];
                    //printf("\nthe end address is %d\n", endloc);
                    cfa = startloc + 1;
                    executeVM = VM[cfa];
                    elseFlg = 0;
                    //inelse = 1;
                }

                if (inIf == 1 && ifLen == 0) {
                    
                    int jumploc = VM[endloc + 2];
                    cfa = jumploc + 1;
                    //printf("\n----------cfa: %d---------\n",cfa);
                    inIf = 0;
                    executeVM = VM[cfa];
                    if (executeVM == cfafin) break;
                    //printf("\n----------haha: %d---------\n",executeVM==cfafin);
                    
                }

                runCodecfa(executeVM);
                if (inIf) ifLen--;
                cfa++;
                if (readFlg) {
                    if (inIf) ifLen--;
                    Stack_push(&data_stack, VM[cfa]);
                    
                    //Stack_pop(&return_stack, &res);
                    //printf("\nchule2 %d--------------------------------s size: %d \n", res, Stack_length(&return_stack));
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
            //printf("\nPop out stack: %d-------------------------------- size: %d \n", res, Stack_length(&return_stack));
            //printf("\n In the stack: ");
            //for (int i = 1; i <= Stack_length(&return_stack); i++) {
            //    printf("%d ", *(return_stack.top - i*sizeof(ElemType)));
            //}
            //printf("\nPop out stack: -------------------------------- size: %d \n", Stack_length(&return_stack));
           
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
    Stack_init(&data_stack);
    Stack_init(&return_stack);
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
    ifFlg = 0;
    elseFlg = 0;
    inIf = 0;
    //cnt = 25;


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
            cfaAnchor = cfaTemp;
            printf("We read a MOTS: %s and find the function in %d\n", output, cfaTemp);
            runCodecfa(cfaTemp);
            break;
        case STRING:
            for (int i = 0; i < output_size; i++){
                executeString[i] = output[i];
                //printf("%c ", output[i]);
            }
            printf("We read a string %s\n", executeString);      
            break;

        default:
            break;
        }
        temp = temp->next;
    }
    printf("\n\n-----End executing-----\n\n");


};


