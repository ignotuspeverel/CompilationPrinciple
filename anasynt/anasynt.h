#ifndef ANASYNT_H
#define ANASYNT_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct node* tree;

struct node
{
    char* label;
    tree lc;
    tree rc;
};

typedef struct number{
    int startptr;
    int endptr;
}number;


bool translate(char* s, char buffer[], number location[], int* bufferLen);

tree assemble(char* name, tree left, tree right);

tree factD(int sptr, int eptr, char* s, char* origin, number location[]);

tree fact(int sptr, int eptr, char* s, char* origin, number location[]);

tree term(int sptr, int eptr, char* s, char* origin, number location[]);

void printTree(tree tr, int blank);

#endif