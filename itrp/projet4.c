#include <stdio.h>
#include <stdlib.h>
#include "interpret.h"


int main (int argc, char** argv)
{
    char *testline = "1 2 - -1 * 3 4 - -5 * + .";
    printf("LAC> %s\n", testline);
    double res = interpret(testline);
    if (flgStack == OK)
        printf("The result of %s is %f.\n", testline, res);

    return 0;
}