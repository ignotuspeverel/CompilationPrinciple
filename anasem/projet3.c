#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "find.h"

int main (int argc, char** argv)
{
    //the test LAC
    int LAC[] = {0, 1, 43, 0, 1, 4, 115, 119, 97, 112, 2, 5};
    int lenLac = 12;

    //3 function name and we create the lexeme
    char* mots = "+ swap non"; 
    lexique a, b, c;
    a.type = MOTS; b.type = MOTS; c.type = MOTS;
    a.start = 0; a.end = 0; b.start = 2; b.end = 5; c.start = 7; c.end = 9;
    
    int res;

    res =find(LAC, lenLac, mots, a);
    if(res == -2) 
        printf("The function %.*s is not in the LAC\n", a.end-a.start+1, mots+a.start);
    else
        printf("The function %.*s is in the LAC and the cfa is: %d\n", a.end-a.start+1, mots+a.start, res);

    res =find(LAC, lenLac, mots, b);
    if(res == -2) 
        printf("The function %.*s is not in the LAC\n", b.end-b.start+1, mots+b.start);
    else
        printf("The function %.*s is in the LAC and the cfa is: %d\n", b.end-b.start+1, mots+b.start, res);

    res =find(LAC, lenLac, mots, c);
    if(res == -2) 
        printf("The function %.*s is not in the LAC\n", c.end-c.start+1, mots+c.start);
    else
        printf("The function %.*s is in the LAC and the cfa is: %d\n", c.end-c.start+1, mots+c.start, res);

    return 0;
}