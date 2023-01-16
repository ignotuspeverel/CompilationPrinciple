#include "compilation.h"

/**
   @brief compile base function
   @param char name[] of function, function address, location in the processeur
 */
void compile_base(char* name, base func, int numProcesseur) {
    //update VM
    VM[vmPtr] = -1;
    int cfa = vmPtr;
    VM[++vmPtr] = numProcesseur;
    vmPtr++;

    //update LAC
    
    LAC[lacPtr] = 0;
    int readptr = 0;
   
    while(name[readptr] != '\0') {
        LAC[lacPtr + readptr + 1] = (int)name[readptr];
        LAC[lacPtr]++;
        readptr++;
    }

    LAC[lacPtr + readptr + 1] = cfa;  //cfa
    LAC[lacPtr + readptr + 2] = lacPtr;     //nfa
    lacPtr += (readptr + 3);

    //update processeur
    processeur[numProcesseur] = func;
};

/**
   @brief compile lac function 1- 0=
   @param char name[] of function, char func[] compile format
 */
void compile_lac(char* name, char* func) {
    //update VM
    bf = "(lit) (fin) + - * = str\0";

    lit.type = MOTS; lit.start = 0; lit.end = 4;

    fin.type = MOTS; fin.start = 6; fin.end = 10;

    pl.type = MOTS; pl.start = 12; pl.end = 12;

    min.type = MOTS; min.start = 14; min.end = 14;

    mul.type = MOTS; mul.start = 16; mul.end = 16;

    eql.type = MOTS; eql.start = 18; mul.end = 18;

    str.type = MOTS; str.start = 20; str.end = 22;

    cfalit = find(LAC, lacPtr+1, bf, lit);
    cfafin = find(LAC, lacPtr+1, bf, fin);
    cfapl = find(LAC, lacPtr+1, bf, pl);
    cfamin = find(LAC, lacPtr+1, bf, min);
    cfamul = find(LAC, lacPtr+1, bf, mul);
    cfaeql = find(LAC, lacPtr+1, bf, eql);
    cfastr = find(LAC, lacPtr+1, bf, str);
    
    int cfa = vmPtr;
    VM[vmPtr++] = cfalit;

    char readchar;
    int num = 0, readptr = 0, numptr = 0;
    char str[12];

    while (func[readptr] != '\0')
    {
        readchar = func[readptr];
        while ((readchar >= '0' && readchar <= '9') || readchar == '-')
        {
            str[numptr] = readchar;
            numptr += 1;
            str[numptr] = '\0';
            if(numptr >= 12)
                printf("ERROR, NUMBER TOO BIG\n");

            if (func[readptr+1] == '\0' && str[0] == '-'){
                readchar = '-';
                break;
            }
            readptr += 1;
            readchar = func[readptr];

            if(readchar == ' '){
                if (numptr == 1 && str[0] == '-'){
                    readchar = '-';
                    break;
                }
                else{
                    if (str[0] == '-') num = - atoi(&str[1]);
                    else num = atoi(str); 
                }
                numptr = 0;
                VM[vmPtr] = num;
                vmPtr++;
                break;
            }
            
        }

        switch (readchar)
        {
        case '+' :
            //cfapl = find(LAC, lacPtr+1, bf, pl);
            VM[vmPtr] = cfapl;
            vmPtr++;
            break;

        case '-' :
            //cfamin = find(LAC, lacPtr+1, bf, min);
            VM[vmPtr] = cfamin;
            vmPtr++;
            break;

        case '*' :
            //cfamul = find(LAC, lacPtr+1, bf, mul);
            VM[vmPtr] = cfamul;
            vmPtr++;
            break;

        case '=' :
            //cfaeql = find(LAC, lacPtr+1, bf, eql);
            VM[vmPtr] = cfaeql;
            vmPtr++;
            break;
            
        default:
            break;

        }
        readptr++;
    }

    cfafin = find(LAC, lacPtr+1, bf, fin);
    VM[vmPtr++] = cfafin;

    //update LAC
    LAC[lacPtr] = 0;
    readptr = 0;
   
    while(name[readptr] != '\0') {
        LAC[lacPtr + readptr + 1] = (int)name[readptr];
        LAC[lacPtr]++;
        readptr++;
    }
    LAC[lacPtr + readptr + 1] = cfa;  //cfa
    LAC[lacPtr + readptr + 2] = lacPtr;     //nfa
    lacPtr += (readptr + 3);

};

/**
   @brief compile init
 */
void compile_init() {
    LAC[0] = 0;
    lacPtr = 1;
    vmPtr = 0;
    compile_base("+", &plus, 0);
    compile_base("swap", &swap, 1);
    compile_base("dup", &mydup, 2);
    compile_base("(lit)", &mylit, 3);
    compile_base("-", &minus, 4);
    compile_base("(fin)", &myfin, 5);
    compile_base(":", &def, 6);
    compile_base("=", &equal, 7);
    compile_base("if", &myif, 8);
    compile_base("drop", &mydrop, 9);
    compile_base("else", &myelse, 10);
    compile_base("recurse", &myrecurse, 11);
    compile_base("*", &multiply, 12);
    compile_base("then", &mythen, 13);
    compile_base(";", &endef, 14);
    compile_base("\"", &notestr, 15);
    compile_base("count", &mycount, 16);
    compile_base("type", &mytype, 17);
    compile_base(".", &mypoint, 18);
    compile_base("cr", &mycr, 19);
    compile_base("calculate", &mycalculate, 20);
    compile_base("str", &mystr, 21);
    compile_lac("0=", "0 =");
    compile_lac("1-", "1 -");
};

/**
   @brief compile code
   @param FILE* f, queue* q
 */
void compile_code(FILE* file, queue* q, queue* e) {
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

    compileFLg = 0; updateLACflg = 0;
    compile_init();
    //for (int i = 0; i < bufferlen; i++) printf("%c", buffer[i]);
    printf("\n");

    int cfa = 0; // cfa of this function
    int jumploc = 0;
    int endifloc = 0;
    
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
            if (compileFLg)
            {
                VM[vmPtr++] = cfalit;
                VM[vmPtr++] = atoi(output);
            }
            else queue_push_back(e, &lex, sizeof(lex));
            
            break;
        case MOTS:
            if (compileFLg) 
            {
                if (updateLACflg) {
                    int funcLen = output_size-1;
                    int nfa = lacPtr;
                    LAC[lacPtr++] = funcLen;
                    for (int j = 0; j < funcLen; j++) 
                        LAC[lacPtr++] = (int)output[j];
                    LAC[lacPtr++] = cfa;
                    LAC[lacPtr++] = nfa;
                    updateLACflg = 0;
                }
                else{
                    if (strcmp(output, ";") == 0) {
                        //printf("jiancedaole\n");
                        endef(); 
                    }
                    else if (strcmp(output, "if") == 0) {
                        int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                        VM[vmPtr++] = cfaTemp;
                        jumploc = vmPtr++;
                    }
                    else if (strcmp(output, "else") == 0) {
                        int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                        VM[vmPtr++] = cfaTemp;
                        VM[jumploc] = vmPtr++;
                        endifloc = vmPtr - 1;
                    }
                    else if (strcmp(output, "then") == 0) {
                        VM[endifloc] = vmPtr - 1;
                    }
                    else{
                        int cfaTemp = find(LAC, lacPtr + 1, buffer, lex);
                        VM[vmPtr++] = cfaTemp;
                    } 
                }
                
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
                if (strcmp(output, ":") == 0) {
                    //printf(":::::jiancedaole\n");
                    cfa = vmPtr;
                    def();
                }
                else queue_push_back(e, &lex, sizeof(lex));
                
            
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
            else queue_push_back(e, &lex, sizeof(lex));
                
            
            break;

        default:
            break;
        }
        temp = temp->next;
    }


};

/**
   @brief display the LAC and the VM
 */
void display() {
    
    int ptr = 1;
    int len = LAC[ptr];

    printf("\n");

    int line = (lacPtr + 1) / 50;
    int readlen = LAC[1]; int disflg = 1;

    for (int l = 0; l <= line; l++){
        printf("LAC  ");
        for (int i = 0; i < 50; i++) {
            printf("%-3d ", (i+l*50));
        }

        printf("\nLAC  ");
        for (int i = 0; i < 50; i++) {
            if (i+l*50 < lacPtr) printf("%-3d ", LAC[i+l*50]);
            else printf("/   ");
        }
        printf("\nLAC  ");
        
        for (int i = 0; i < 50; i++) {
            if (i+l*50 < 2) printf("    ");
            else{
                if (0 < i+l*50 < lacPtr) {
                    if(disflg > 0){
                        printf("%-3c ", LAC[i+l*50]);
                        readlen--;
                        if(readlen == 0) {
                            disflg = -2;
                            readlen = LAC[i+l*50 + 3]; 
                        }
                    }
                    else {
                        printf("    ");
                        disflg++;
                    }
                }
            }
        }
        printf("\n\n");    

    }
    printf("\n");

    line = vmPtr / 50;
    for (int l = 0; l <= line; l++) {
        printf("VM  ");
        for (int i = 0; i < 50; i++) {
            printf("%-3d ", (i+l*50));
        }

        printf("\nVM  ");
        for (int i = 0; i < 50; i++) {
            if (i+l*50 < vmPtr) printf("%-3d ", VM[i+l*50]);
            else printf("/   ");
        }
        printf("\n\n");

    }
   
    


};

/**
   @brief base function 0, '+', plus
 */
void plus(){
    printf("\n---We execute plus()---\n");
    ElemType a, b;
    if (Stack_pop(&data_stack, &a) == OK && Stack_pop(&data_stack, &b) == OK)
        Stack_push(&data_stack, b+a);
    else{
        flgStack = ERROR;
        printf("pop error");
        return;
    }
    printf("\n---We have executed plus()---\n");
};

/**
   @brief base function 1, 'swap'
 */
void swap(){};

/**
   @brief base function 2, 'dup', duplicate the stack top
 */
void mydup(){};

/**
   @brief base function 3, '(lit)', next number push into the stack
 */
void mylit(){ readFlg = 1; };

/**
   @brief base function 4, '-', minus
 */
void minus(){};

/**
   @brief base function 5, '(fin)', end of a function
 */
void myfin(ElemType *e) {
    Stack_pop(&return_stack ,e);
};

/**
   @brief base function 6, ':', start to define a function
 */
void def(){ 
    compileFLg = 1; 
    updateLACflg = 1;
};

/**
   @brief base function 7, '=', check the top of the 2 elements in stack is equal or not
   @return equal -1; not equal 0
 */
void equal(){};

/**
   @brief base function 8, 'if', check the stack top is -1 or 0
   @return -1 else; 0 then
 */
void myif(){};

/**
   @brief base function 9, 'drop', pop the stack top
 */
void mydrop(){};

/**
   @brief base function 10, 'else'
 */
void myelse(){};

/**
   @brief base function 11, 'recurse', go back to this function and do again
 */
void myrecurse(){};

/**
   @brief base function 12, '*', multiply
 */
void multiply(){};

/**
   @brief base function 13, 'then', end the if else
 */
void mythen(){};

/**
   @brief base function 14, ';', end define
 */
void endef(){ 
    //printf("vmptr %d\n", vmPtr);
    VM[vmPtr++] = cfafin;
    compileFLg = 0;
};

/**
   @brief base function 15, '"', note that a string is coming
 */
void notestr(){};

/**
   @brief base function 16, 'count', how a string is push into the stack
 */
void mycount(){
    printf("\n---We execute count()---\n");
    int res;
    int len;
    Stack_pop(&data_stack, &res);
    len = VM[res];
    Stack_push(&data_stack, res+1);

    Stack_push(&data_stack, len);
    
    printf("\n---We have executed count()---\n");
};

/**
   @brief base function 17, 'type', type the string in the stack top
 */
void mytype(){
    printf("\n---We execute type()---\n\n");
    int len;
    int add;
    Stack_pop(&data_stack, &len);
    Stack_pop(&data_stack, &add);
    
    for (int i = 0; i < len; i++) {
        char p = (char)VM[add+i];
        printf("%c", p);
    }
    printf("\n\n---We have executed type()---\n\n");
};

/**
   @brief base function 18, '.', type the value in the stack top
 */
void mypoint(){
    printf("\n---We execute point()---\n");
    int res;
    Stack_pop(&data_stack, &res);
    printf("\nThe top of the stack is: %d\n", res);
    printf("\n---We have executed point()---\n");

};

/**
   @brief base function 19, 'cr', print \\n
 */
void mycr(){};

/**
   @brief base function 20, 'calculate', calculate a string
 */
void mycalculate(){};

/**
   @brief base function 21, 'str', tell the executer there is a string coming
 */
void mystr(){
    strFlg = 1;
};