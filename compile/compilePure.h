#ifndef COMPILATION_H
#define COMPILATION_H
#define LACSize 10000
#define VMSize 10000
#define PSize 50


#include "../analex/analex.h"
#include "../library/queue.h"
#include "../anasem/find.h"
#include <string.h>
#include "../library/stack.h"

Stack data_stack, return_stack;

Stack_err_t flgStack;

typedef void (*base)();

base processeur[PSize];
int LAC[LACSize];
int VM[VMSize];
int lacPtr; 
int vmPtr;
int compileFLg, updateLACflg, strFlg, readFlg, ifFlg, elseFlg, inIf, ifLen;
int cfaAnchor;

char* bf;

lexique lit;
  

lexique fin;


lexique pl;
 

lexique min;
   

lexique mul;
  

lexique eql;


lexique str;

int cfalit, cfafin, cfapl, cfamin, cfamul, cfaeql, cfastr;


    

/**
   @brief compile base function
   @param char name[] of function, function address, location in the processeur
 */
void compile_base(char* name, base func, int numProcesseur);

/**
   @brief compile lac function
   @param char name[] of function, char func[] compile format
 */
void compile_lac(char* name, char* func);

/**
   @brief compile init
 */
void compile_init();

/**
   @brief compile code
   @param FILE* f, queue* q
 */
void compile_code(FILE *file, queue* q, queue *e);

void display();

//Now we define the base function
/**
   @brief base function 0, '+', plus
 */
void plus();

/**
   @brief base function 1, 'swap'
 */
void swap();

/**
   @brief base function 2, 'dup', duplicate the stack top
 */
void mydup();

/**
   @brief base function 3, '(lit)', next number push into the stack
 */
void mylit();

/**
   @brief base function 4, '-', minus
 */
void minus();

/**
   @brief base function 5, '(fin)', end of a function
 */
void myfin(ElemType* e);

/**
   @brief base function 6, ':', start to define a function
 */
void def();

/**
   @brief base function 7, '=', check the top of the 2 elements in stack is equal or not
   @return equal -1; not equal 0
 */
void equal();

/**
   @brief base function 8, 'if', check the stack top is -1 or 0
   @return -1 else; 0 then
 */
void myif();

/**
   @brief base function 9, 'drop', pop the stack top
 */
void mydrop();

/**
   @brief base function 10, 'else'
 */
void myelse();

/**
   @brief base function 11, 'recurse', go back to this function and do again
 */
void myrecurse();

/**
   @brief base function 12, '*', multiply
 */
void multiply();

/**
   @brief base function 13, 'then', end the if else
 */
void mythen();

/**
   @brief base function 14, ';', end define
 */
void endef();

/**
   @brief base function 15, '"', note that a string is coming
 */
void notestr();

/**
   @brief base function 16, 'count', how a string is push into the stack
 */
void mycount();

/**
   @brief base function 17, 'type', type the string in the stack top
 */
void mytype();

/**
   @brief base function 18, '.', type the value in the stack top
 */
void mypoint();

/**
   @brief base function 19, 'cr', print \\n
 */
void mycr();

/**
   @brief base function 20, 'calculate', calculate a string
 */
void mycalculate();

/**
   @brief base function 21, 'str', tell the executer there is a string coming
 */
void mystr();

#endif