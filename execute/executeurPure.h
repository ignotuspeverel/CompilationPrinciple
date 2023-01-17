#ifndef EXECUTEURPURE_H
#define EXECUTEURPURE_H

#include "../compile/compilation.h"

char executeString[1000];

/**
   @brief run the code VM[cfa] in a recursive way
   @param int cfa
 */
void runCodecfa(int cfa);

/**
   @brief execute the code
   @param FILE* f, queue* q
 */
void execute(FILE *file, queue* q);


#endif