#ifndef INTERPRET_H
#define INTERPRET_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../library/stack.h"

Stack dataStack;

Stack_err_t flgStack;

void plus();

void minus();

void times();

/**
 * @brief interpret a char*
 * @param char* input
 * @return the output value of the input
 */
int interpret(char* input);

#endif