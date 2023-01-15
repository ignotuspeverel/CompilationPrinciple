#ifndef EXECUTEUR_H
#define EXECUTEUR_H

#include "../compile/compilation.h"
#include "../library/stack.h"

Stack data_stack, return_stack;

/**
   @brief execute the code
   @param FILE* f, queue* q
 */
void execute(FILE *file, queue* q);


#endif