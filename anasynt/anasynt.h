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

/**
 * @brief translate a string input to a BNF string
 * @param input string, output buffer, an array to store the location of number, the length of the output 
 */
bool translate(char* s, char buffer[], number location[], int* bufferLen);

/**
 * @brief assemble a tree with lc and rc
 * @param a label for the node, lc, rc
 */
tree assemble(char* name, tree left, tree right);

/**
 * @brief recognize a factD
 * @param startptr, endptr, input BNF string, original string, an array to store the location of number
 */
tree factD(int sptr, int eptr, char* s, char* origin, number location[]);

/**
 * @brief recognize a fact
 * @param startptr, endptr, input BNF string, original string, an array to store the location of number
 */
tree fact(int sptr, int eptr, char* s, char* origin, number location[]);

/**
 * @brief recognize a term
 * @param startptr, endptr, input BNF string, original string, an array to store the location of number
 */
tree term(int sptr, int eptr, char* s, char* origin, number location[]);

/**
 *  @brief print the tree
 */
void printTree(tree tr, int blank);

#endif