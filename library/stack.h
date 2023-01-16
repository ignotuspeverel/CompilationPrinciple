#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//define a stack error type
typedef enum{
    OK    =1,
    ERROR =0
}Stack_err_t;

typedef int ElemType; 
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct{
    ElemType *base;
    ElemType *top;
    int stackSize;
}Stack;

/**
 * @brief Init a stack structure
 * @param stack s
 * @return Stack_err_t status
 */
Stack_err_t Stack_init(Stack *s);

/**
 * @brief Push an element to a stack
 * @param Stack *s and Elemtype e
 * @return Stack_err_t status
 */
Stack_err_t Stack_push(Stack *s,ElemType e);

/**
 * @brief Pop an element to a stack
 * @param Stack *s and Elemtype *e
 * @return Stack_err_t status
 */
Stack_err_t Stack_pop(Stack *s,ElemType *e);

/**
 * @brief calculate the number of the elements of the stack
 * @param Stack *s
 * @return int
 */
int Stack_length(Stack *s);

#endif