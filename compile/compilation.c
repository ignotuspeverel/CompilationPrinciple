#include "compilation.h"

/**
   @brief compile base function
   @param char name[] of function, function address, location in the processeur
 */
void compile_base(char* name, base* func, int numProcesseur) {
    //update VM
    VM[vmPtr] = -1;
    VM[++vmPtr] = numProcesseur;
    int cfa = vmPtr++;

    //update LAC
    lacPtr++;
    LAC[lacPtr] = 0;
    int readptr = 0;
   
    while(name[readptr] != '\0') {
        LAC[lacPtr + readptr + 1] = (int)name[readptr];
        LAC[lacPtr]++;
        readptr++;
    }
    LAC[lacPtr + readptr] = cfa;  //cfa
    LAC[lacPtr + readptr + 1] = lacPtr;     //nfa
    lacPtr += (readptr + 1);

    //update processeur
    processeur[numProcesseur] = func;
};

/**
   @brief compile lac function 1- 0=
   @param char name[] of function, char func[] how to compile
 */
void compile_lac(char* name, char* func) {
    //update VM
    char* bf = "(lit) (fin) + - = \0";

    lexique lit;
    lit.type = MOTS; lit.start = 0; lit.end = 4;

    lexique fin;
    fin.type = MOTS; lit.start = 6; lit.end = 10;

    lexique pl;
    pl.type = MOTS; pl.start = 12; pl.end = 12;

    lexique min;
    min.type = MOTS; min.start = 14; min.end = 14;

    lexique mul;
    mul.type = MOTS; mul.start = 16; mul.end = 16;

    int cfa = vmPtr;

    int cfalit = find(LAC, lacPtr+1, bf, lit);

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
            if( numptr >= 12)
                printf("ERROR, NUMBER TOO BIG\n");
            readptr += 1;
            readchar = func[readptr];

            if(readchar == ' '){
                if (numptr == 1 && str[0] == '-')
                    readchar = '-';
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
            int cfapl = find(LAC, lacPtr+1, bf, pl);
            VM[vmPtr] = cfapl;
            vmPtr++;
            break;

        case '-' :
            int cfamin = find(LAC, lacPtr+1, bf, min);
            VM[vmPtr] = cfamin;
            vmPtr++;
            break;

        case '*' :
            int cfamul = find(LAC, lacPtr+1, bf, mul);
            VM[vmPtr] = cfamul;
            vmPtr++;
            break;
            
        default:
            break;

        }
        readptr++;
    }

    int cfafin = find(LAC, lacPtr+1, bf, fin);
    VM[vmPtr++] = cfafin;

    //update LAC
    lacPtr++;
    LAC[lacPtr] = 0;
    readptr = 0;
   
    while(name[readptr] != '\0') {
        LAC[lacPtr + readptr + 1] = (int)name[readptr];
        LAC[lacPtr]++;
        readptr++;
    }
    LAC[lacPtr + readptr] = cfa;  //cfa
    LAC[lacPtr + readptr + 1] = lacPtr;     //nfa
    lacPtr += (readptr + 1);

};

/**
   @brief compile init
 */
void compile_init() {
    LAC[0] = 0;
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
    compile_lac("1-", "1 -");
    compile_lac("0=", "0 =");
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

    printf("LAC  ");
    for (int i = 1; i < lacPtr; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("LAC  ");
    for (int i = 1; i < lacPtr; i++) {
        printf("%d ", LAC[i]);
    }
    printf("\n");
    printf("LAC    ");
    for (int i = 1; i < lacPtr; i++) {
        i++;
        int j = 0;
        while(j < len) {
            char c;
            c = LAC[i + j + 1];
            printf("%c ", &c);

        }
        i += (len+3);
        printf("    ");
    }
    printf("\n");
    

    printf("VM  ");
    for (int i = 0; i < vmPtr; i++) {
        printf("%d ", i);
    }

    printf("VM  ");
    for (int i = 0; i < vmPtr; i++) {
        printf("%d ", VM[i]);
    }


};