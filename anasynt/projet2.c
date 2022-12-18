#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "anasynt.h"

int main (int argc, char** argv)
{
    char* s = " -(1-2)+(3-4)x(-5)";
    char *trans;
    int charLen = strlen(s);
    int bufferLength;
    char buffer[2*(charLen + 1)];
    number location[2*(charLen + 1)];
    if(translate(s, buffer, location, &bufferLength)) {trans = buffer;}
    else {
        printf("Translation error. Doesn't recogonize this term\n");
        return 1;
    }
    printf("Test of string %s\n", s);
    printf("The translation %.*s\n", bufferLength, trans);
    tree tr = term(0, bufferLength-1, trans, s, location);
    if (tr != NULL) printTree(tr, 0);
    else printf("Doesn't recogonize this term\n");
    return 0;
}