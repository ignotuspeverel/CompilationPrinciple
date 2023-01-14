#ifndef ANALEX_H
#define ANALEX_H

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../library/queue.h"

#define REGEX_COMMENT          "[\n| ]?\\( .*\\)[\n]?|[\n| ]?\\\\[^\n]*[\n]|[\n| ]?\\( .*[\n].*\\)[\n]?"  
#define REGEX_STRING           "\" [^\"]*\"|\" [^\"]*[\n][^\"]*\""
#define REGEX_IDENTIFIER       "[^\" \n]+" 
#define REGEX_INTEGER          "(\\-|\\+)?[0-9]+(\n| )" 

typedef enum lex_types {
    MOTS,
    INT,
    STRING,
} lex_types;

typedef struct lexique {
    lex_types type;
    int start;
    int end;
} lexique;

bool lex_analyse(FILE *file, queue *q);

void display_queue(char buffer[], queue *q);

#endif