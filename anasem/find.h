#ifndef FIND_H
#define FIND_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../analex/analex.h"

/**
 * @brief find the cfa by LAC
 * @param LAC, length of the Lac, origin file, the input lexeme
 */
int find(int lac[], int length, char* origin, lexique lex);

#endif