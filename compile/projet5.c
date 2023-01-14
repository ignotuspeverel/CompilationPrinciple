#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "compilation.h"

int main (int argc, char** argv)
{
    FILE* file;
    queue queue_res;
    queue_init(&queue_res);

    if ((file = fopen("./testCompile.lac", "r")) == NULL) {
        perror("Error opening file");
        return 1;
    }
    lex_analyse(file, &queue_res);

    compile_code(&queue_res);
    printf("%d\n",lacPtr);
    printf("%d\n",vmPtr);
    display();

    fclose(file);
    return 0;
}