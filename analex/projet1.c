#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "analex.h"

int main (int argc, char** argv)
{
    FILE* file;
    queue queue_res;
    queue_init(&queue_res);

    if ((file = fopen("../factorielle.lac", "r")) == NULL) {
        perror("Error opening file");
        return 1;
    }
    lex_analyse(file, &queue_res);
    fclose(file);
    return 0;
}