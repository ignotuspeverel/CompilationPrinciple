#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include "executeur.h"

int main (int argc, char** argv)
{
    FILE* file;
    queue queue_res;
    queue queue_exe;
    queue_init(&queue_res);
    queue_init(&queue_exe);

    if ((file = fopen("../lac/essai.lac", "r")) == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nAnalyzing the file:\n");
    lex_analyse(file, &queue_res);

    printf("Compiling file:\n");
    compile_code(file, &queue_res, &queue_exe);
    
    printf("\nNow we display LAC and VM after compilation:\n");
    display();

    //printf("\nqesize: %d\n", queue_exe.size);

    execute(file, &queue_exe);

    fclose(file);
    return 0;
}