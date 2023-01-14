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
   @param char name[] of function, char func[] how to compile
 */
void compile_lac(char* name, char* func) {
    //update VM
    char* bf = "(lit) (fin) + - * = \0";

    lexique lit;
    lit.type = MOTS; lit.start = 0; lit.end = 4;

    lexique fin;
    fin.type = MOTS; fin.start = 6; fin.end = 10;

    lexique pl;
    pl.type = MOTS; pl.start = 12; pl.end = 12;

    lexique min;
    min.type = MOTS; min.start = 14; min.end = 14;

    lexique mul;
    mul.type = MOTS; mul.start = 16; mul.end = 16;

    lexique eql;
    eql.type = MOTS; eql.start = 18; mul.end = 18;

    int cfa = vmPtr;

    int cfalit, cfafin, cfapl, cfamin, cfamul, cfaeql;
    cfalit = find(LAC, lacPtr+1, bf, lit);

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
            cfapl = find(LAC, lacPtr+1, bf, pl);
            VM[vmPtr] = cfapl;
            vmPtr++;
            break;

        case '-' :
            cfamin = find(LAC, lacPtr+1, bf, min);
            VM[vmPtr] = cfamin;
            vmPtr++;
            break;

        case '*' :
            cfamul = find(LAC, lacPtr+1, bf, mul);
            VM[vmPtr] = cfamul;
            vmPtr++;
            break;

        case '=' :
            cfaeql = find(LAC, lacPtr+1, bf, eql);
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
    //compile_lac("1-", "1 -");
    compile_lac("0=", "0 =");
    compile_lac("1-", "1 -");
};

/**
   @brief compile code
   @param queue* q
 */
void compile_code(queue* q) {
    compile_init();
};

void display() {
    
    int ptr = 1;
    int len = LAC[ptr];

    printf("\n");

    printf("LAC  ");
    for (int i = 0; i < lacPtr; i++) {
        printf("%d ", LAC[i]);
    }
    printf("\n");

    printf("VM  ");
    for (int i = 0; i < vmPtr; i++) {
        printf("%d ", i);
    }

    printf("\n");

    printf("VM  ");
    for (int i = 0; i < vmPtr; i++) {
        printf("%d ", VM[i]);
    }
    printf("\n");


};

/**
   @brief base function 0, '+', plus
 */
void plus(){};

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
void mylit(){};

/**
   @brief base function 4, '-', minus
 */
void minus(){};

/**
   @brief base function 5, '(fin)', end of a function
 */
void myfin(){};

/**
   @brief base function 6, ':', start to define a function
 */
void def(){};

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
void endef(){};

/**
   @brief base function 15, '"', note that a string is coming
 */
void notestr(){};

/**
   @brief base function 16, 'count', how a string is push into the stack
 */
void mycount(){};

/**
   @brief base function 17, 'type', type the string in the stack top
 */
void mytype(){};

/**
   @brief base function 18, '.', type the value in the stack top
 */
void mypoint(){};

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
void mystr(){};