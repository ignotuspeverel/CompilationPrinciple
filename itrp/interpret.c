#include "interpret.h"

void plus(){
    ElemType a, b;
    if (Stack_pop(&dataStack, &a) == OK && Stack_pop(&dataStack, &b) == OK)
        Stack_push(&dataStack, b+a);
    else{
        flgStack = ERROR;
        printf("pop error");
        return;
    }
}

void minus(){
    ElemType a, b;
    if (Stack_pop(&dataStack, &a) == OK && Stack_pop(&dataStack, &b) == OK)
        Stack_push(&dataStack, b-a);
    else{
        flgStack = ERROR;
        printf("pop error");
        return;
    }
}

void times(){
    ElemType a, b;
    if (Stack_pop(&dataStack, &a) == OK && Stack_pop(&dataStack, &b) == OK)
        Stack_push(&dataStack, b*a);
    else{
        flgStack = ERROR;
        printf("pop error");
        return;
    }
}

int interpret(char* input){
    flgStack = OK;
    int readptr = 0, numptr = 0; double res = 0;
    char readchar; 
    char str[12];
    Stack_init(&dataStack);

    while (input[readptr] != '.')
    {
        readchar = input[readptr];
        while ((readchar >= '0' && readchar <= '9') || readchar == '-')
        {
            str[numptr] = readchar;
            numptr += 1;
            str[numptr] = '\0';
            if( numptr >= 12)
                printf("ERROR, NUMBER TOO BIG\n");
            readptr += 1;
            readchar = input[readptr];

            if(readchar == ' '){
                if (numptr == 1 && str[0] == '-')
                    readchar = '-';
                else{
                    double d;
                    if (str[0] == '-') d = - atof(&str[1]);
                    else d = atof(str); 
                    Stack_push(&dataStack, d);
                }
                numptr = 0;
                break;
            } 
        }
        switch (readchar)
        {
        case '+' :
            plus();
            break;

        case '-' :
            minus();
            break;

        case '*' :
            times();
            break;
            
        default:
            break;

        }
        if(flgStack == ERROR) {
            printf("Stack pop error occur, please check.");
            return ERROR; 
        }
        readptr++;
    }
    Stack_pop(&dataStack, &res);
    return res;
}