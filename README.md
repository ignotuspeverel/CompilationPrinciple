# PROJECT FOR CS448

[TOC]



<div style="page-break-after:always;"></div>

## **Part0 Introduction of the project**

The project contains several parts.  The first few (Part 1, Part 2, Part3) concentrates on the sub section of programming language theory. ( ex. lexical analysis,  grammatical analysis, etc. )  The major task is to compile and execute the  document "factorielle.lac". So in the rest of the project, we will try to create a LAC(Symbols Table) and a VM(Virtual Machine) for compilation and execution. The project has improved my understanding of programming languages, applications of the abstract data structure (stack, queue and tree) and the skills of object-oriented programming with language C.

## **Part1 Analyse lexicale**

For this part, I used regular expressions to distinguish between numbers, words and strings. All the detailed files are in the folder **analex**.

### **1.1 REGULAR EXPRESSIONS:**

Here are the regular expressions used:

```ABAP
#define REGEX_COMMENT    "[\n| ]?\\( .*\\)[\n]?|[\n| ]?\\\\[^\n]*[\n]|[\n| ]?\\( ([^\\)\n]*(\n)?)*\\)?"
#define REGEX_STRING     "\" [^\"]*\"|\" [^\"]*[\n][^\"]*\""
#define REGEX_IDENTIFIER "[^\" \n]+" 
#define REGEX_INTEGER    "(\\-|\\+)?[0-9]+(\n| )" 

```

In the main function, I read the file to one buffer and use the regular expressions in an order of comment, string, integer and word:

<img src=".\src\mainfuncLex.jpg" style="zoom:67%;" />

### **1.2 STRUCT FOR LEXEME:**

For content that are recognized, I create a struct to store its type, its beginning and ending in the file:

```c
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
```



### **1.3 DATA STRUCTURE QUEUE:**

I also write a queue data structure to store my created structure lexique.

Code from **queue.h**:

```c
typedef struct queue_node {
    void *element;
    int element_size;
    struct queue_node *prev;
    struct queue_node *next;
} q_node;

typedef struct queue_manager
{
    int size;
    q_node *front;
    q_node *rear;

}queue;

/**
 * @brief queue manager creation, return an empty queue
 */
queue *queue_create();

/**
 * @brief queue manager creation, return an empty queue
 */
void queue_init(queue* queue_ptr);

/**
 * @brief Enqueue element at the end of queue
 * @param queue pointer, element pointer, int for element size
 */
bool queue_push_back(queue *queue_ptr, void *element, int element_size);
```

Finally a display function to display them from queue.

### **1.4 USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet1.c analex.c ../library/queue.c -o test
$ ./test
```

### **1.5 RESULT:**

![](.\src\lexresult.jpg)

## **Part 2 Analyse syntaxique**

For this part, I used a BNF. All the detailed files are in the folder **anasynt**.

### **2.1 BNF**:

The BNF I used is:



![](D:\plt\src\BNF.jpg)

| **N**    | **NUMBER**     |
| -------- | -------------- |
| **O, F** | **'(' ,  ')'** |
| **P**    | **'+'**        |
| **M**    | **'-'**        |
| **H**    | **'x'**        |

The whole function is designed based on a recursive idea.

### **2.2 Functions**:

- **translate:** to recognize a string and replace it with the symbols above.

- **assemble:** to assemble a tree with left child and right child.

- **factD:** to recognize a **factD.**

- **fact:**  to recognize a **fact**.

- **term:** to recognize a **term**.

- **printTree:** to print a tree.

Code from **anasynt.h**:

```c
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
```

### **2.3 USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet2.c anasynt.c -o test
$ ./test
```

### **2.4 RESULT:**

![](D:\plt\src\anasyntRes.jpg)

<div style="page-break-after:always;"></div>

## **Part3 Analyse sémantique et compilation des fonctions du processeur**

This part we write a function find to get the CFA of a lexeme in the LAC.

All the code is in the folder **anasem**.

### **3.1 FUNCTION**:

The test LAC is :

```c
int LAC[] = {0, 1, 43, 0, 1, 4, 115, 119, 97, 112, 2, 5};
```

This LAC has 2 function: '+' and "swap" 



The test string of functions is:

```c
char* mots = "+ swap non"; 
```

This string has 3 functions '+', "swap" and "non".



We then create the lexeme a, b and c by using the struct **lexique**.

The function of **find**:

```c
/**
 * @brief find the cfa by LAC
 * @param LAC, length of the Lac, origin file, the input lexeme
 */
int find(int lac[], int length, char* origin, lexique lex);
```

### **3.2 USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet3.c find.c -o test
$ ./test
```

### **3.3 RESULT:**

<img src="D:\plt\src\res3.jpg" style="zoom:100%;" />



## **Part4 Interprétation**

In this section we will compute the suffix expressions. All the code is in the folder **itrp**.

### **4.1 DATA STRUCTURE STACK:**

First we write a data structure **Stack** for the process. All the code is in the folder library. It can push and pop element.

Code from **stack.h**:

```c
//define stack error type
typedef enum{
    OK    =1,
    ERROR =0
}Stack_err_t;

typedef double ElemType; 
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
```

### **4.2 FUNCTIONS:**

Our main function is **interpret(char* input)**. Also we have other function to do the plus, minus and multiply.

Code form **interpret.h**:

```c
void plus();

void minus();

void times();

/**
 * @brief interpret a char*
 * @param char* input
 * @return the output value of the input
 */
int interpret(char* input);
```

We show one of the function **plus()**, this function also ensures that we will be informed when the stack is empty.

Code from **interpret.c**:

```c
void plus(){
    ElemType a, b;
    if (Stack_pop(&dataStack, &a) == OK && Stack_pop(&dataStack, &b) == OK)
        Stack_push(&dataStack, b+a);
    else{
        flgStack = ERROR;
        printf("pop error");
        return;
    }
}
```

### **4.3 USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet4.c interpret.c ../library/stack.c -o test
$ ./test
```

### **4.4 RESULT:**

<img src="D:\plt\src\res5.jpg" style="zoom:100%;" />



## **Part5 Compilation**

In this part, we do the compilation and output the LAC and the VM. We test the compilation in 3 files in the folder **lac**. All the code is in the folder **compile**.

### **5.1 FUNCTIONS**

See the file **compilation.h**.

The LAC and VM are put in the array. The function processor is an array with the type void*.

Also for the compilation, there are some integer that store the **Cfa** of some base function.

```c
typedef void (*base)();
base processeur[PSize];

int LAC[LACSize];
int VM[VMSize];
int lacPtr; 
int vmPtr;

int cfalit, cfafin, cfapl, cfamin, cfamul, cfaeql, cfastr;

```

There are four functions for the compilation. 

- **compile_base()** : compile the base functions, update the LAC and VM.

- **compile_lac()** : compile the LAC functions (0=, 1-), update the LAC and VM.

- **compile_init()** : do the compile_base() and the compile_lac().

- **compile_code()** : compile the code that are defined in the document, update the LAC and VM.

The display function is to output the result clearly.

```c
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
   @param FILE* f, queue* q for compilation, and queue* e for execution
 */
void compile_code(FILE *file, queue* q, queue *e);

/**
   @brief display the LAC and VM
 */
void display();
```

Also I declare all the base function.

Part of the file:

```c
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

```

### **5.2 USAGE:**

- **essai.lac**

```bash
$ gcc projet5essai.c ../analex/analex.c ../library/queue.c ../library/stack.c compilation.c ../execute/executeur.c ../anasem/find.c ../anasynt/anasynt.c -o test
$ ./test
```

- **incr.lac**

```bash
$ gcc projet5incr.c ../analex/analex.c ../library/queue.c ../library/stack.c compilation.c ../execute/executeur.c ../anasem/find.c ../anasynt/anasynt.c -o test
$ ./test
```

- **factorielle.lac**

```bash
$ gcc projet5.c ../analex/analex.c ../library/queue.c ../library/stack.c compilation.c ../execute/executeur.c ../anasem/find.c ../anasynt/anasynt.c -o test
$ ./test
```

### **5.3 RESULT:**

- **essai.lac**

![](D:\plt\src\res5essai.jpg)

**LAC:**

| 146  | 147  | 148  | 149  | 150  | 151  | 152  | 153  |
| :--- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 5    | 101  | 115  | 115  | 97   | 105  | 52   | 146  |
| len  | e    | s    | s    | a    | i    | Cfa  | Nfa  |



**VM:**

| 52   | 53   | 54   | 55   | 56   | 57   | 58   | 59   | 60   | 61    | 62   | 63    |
| :--- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ----- |
| 42   | 7    | 66   | 111  | 110  | 106  | 111  | 117  | 114  | 32    | 34   | 10    |
| str  | 7    | B    | o    | n    | j    | o    | u    | r    | count | type | (fin) |



The other two documents are quite the same.

- **incr.lac**

![](D:\plt\src\res5incr.jpg)

- **fact.lac**

![](D:\plt\src\res5fact.jpg)



## Part6 **Execution**

In this part, we do the execution based on the LAC and the VM. We test the execution in 3 files in the folder **lac**. All the code is in the folder **execute**.

The procedure is as follows:

1. Lexical analysis and put all the code in the document in a queue.
2. Perform compilation and create the LAC and VM.
3. Execute the code based on the LAC and VM.

### **6.1 FUNCTIONS**

See the file **executeur.h**.

We have two functions:

- **runCodeCfa()** :  run the code VM[Cfa] in a recursive way

- **execute()** : execute the code with the queue queue_exe.

```c
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
```

All the base functions are written in the **compilation.c**. Note for the function **calculate**, we wrote some new functions in the part **anasynt** to calculate a tree.

Code in anasynt.h:

```c
/**
   @brief do the calucate of a tree
*/
int cal(tree tr);

/**
   @brief test if a char* is a digit
*/
int isNum(char* s);
```



### **6.2 USAGE and RESULT:**

We have two types of output. One is used for debug and the other only has the output. 

For different documents, we can just change the first variable when we compile in bash.

We have: **projet6essai.c	projet6incr.c	porjet6fact.c**

#### **6.2.1 Debug version:**

The debug version use **executeur.c** and **../compile/compilation** to compile, which allows us to observe: how the functions are executed in the VM. Actually in the code I also write a few lines to monitor the return stack. The results with the stack monitor are given below. Since the execution output would be too long, I have **annotated** them.  

```bash
We read a MOTS: essai and find the function in 52

Push into stack: 52-------------------------------- size: 1 

 In the stack: 52 

NOW we start to execute the VM[52]

Push into stack: 42-------------------------------- size: 2 

 In the stack: 42 52 
```

We use the **essai.lac** as an example because it is easy and the execution is rather short. 

##### **usage:**

```bash
$ gcc projet6essai.c executeur.c ../analex/analex.c ../library/queue.c ../library/stack.c ../compile/compilation.c ../anasem/find.c ../anasynt/anasynt.c -o test
$ ./test
```

##### **result:**

Part of the output

```bash
Compiling file:
: essai ( -- ) " Bonjour" count type ;
essai

-----Start executing-----
We read a MOTS: essai and find the function in 52

NOW we start to execute the VM[52]

NOW we start to execute the VM[42]

Base function: We have executed the VM[42]

NOW we start to execute the VM[32]

---We execute count()---

---We have executed count()---

Base function: We have executed the VM[32]

NOW we start to execute the VM[34]

---We execute type()---

Bonjour

---We have executed type()---


Base function: We have executed the VM[34]

LAC function: We have executed the VM[52]


-----End executing-----
```

#### **6.2.2 Pure version:**

The Pure version use **executeurPure.c** and **../compile/compilePure** to compile, which only gives us the result of the execution.

We use the **incr.lac** and **factorielle.lac** as an example. 

##### **usage:**

```bash
$ gcc projet6fact.c executeurPure.c ../analex/analex.c ../library/queue.c ../library/stack.c ../compile/compilePure.c ../anasem/find.c ../anasynt/anasynt.c -o test
$ ./test
```

##### **result:**

Part of the output

- **incr.lac**

```bash
Compiling file:
: INCR 1 + ;
: 2+. INCR INCR . ;
123 2+.

-----Start executing-----

 125 
 
-----End executing-----
```

- **factorielle.lac**

```bash
Compiling file:
\ Fichier "factorielle.lac"

( Ce fichier est un "exemple" étudié pour tester 
l'analyseur lexical écrit en phase 1 du projet)

: fact ( n -- n!)
    dup 0= 
    if
        drop 1
    else 
        dup 1- recurse * 
    then ;

: go  ( n -- )
    " Factorielle" count type
    dup .
    " vaut : 
" count type
    fact . cr ; 
" -(1-2)+(3-4)x(-5)" calculate go

-----Start executing-----

Factorielle 6 vaut : 
 720 


-----End executing-----
```

## **Part7 Conclusion (Strengths and weaknesses)**

I managed to compile the file factorielle.lac and find the factorial of 6. This project has been a great improvement to my ability. But there may be better solutions to a number of problems, such as the first part where I read the file twice while requesting an extra check array, which does not perform well in terms of time complexity and space complexity, or the fact that sometimes there are no bounds or memory checks, which may cause overflow or memory leak problems.

Hope my code gets better and better.
