# PROJECT FOR CS448

## Part1 Analyse lexicale

For this part, I used regular expressions to distinguish between numbers, words and strings. All the detailed files are in the folder **analex**.

### **REGULAR EXPRESSIONS:**

Here are the regular expressions used:

<img src=".\src\regexexpr.jpg" style="zoom:67%;" />

In the main function, I read the file to one buffer and use the regular expressions in an order of comment, string, integer and word:

<img src=".\src\mainfuncLex.jpg" style="zoom:67%;" />

### **STRUCT FOR LEXEME:**

For content that are recognized, I create a struct to store its type, its beginning and ending in the file:

<img src=".\src\lexstruct.jpg" alt="lexstruct" style="zoom:67%;" />

### **DATA STRUCTURE QUEUE:**

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

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet1.c analex.c ../library/queue.c -o test
$ ./test
```

### **RESULT:**

![](.\src\lexresult.jpg)

## Part 2 Analyse syntaxique

For this part, I used a BNF. All the detailed files are in the folder **anasynt**.

### **BNF**:

The BNF I used is:



![](D:\plt\src\BNF.jpg)

| **N**    | **NUMBER**     |
| -------- | -------------- |
| **O, F** | **'(' ,  ')'** |
| **P**    | **'+'**        |
| **M**    | **'-'**        |
| **H**    | **'x'**        |

The whole function is designed based on a recursive idea.

### **Functions**:

**translate:** to recognize a string and replace it with the symbols above.

**assemble:** to assemble a tree with left child and right child.

**factD:** to recognize a **factD.**

**fact:**  to recognize a **fact**.

**term:** to recognize a **term**.

**printTree:** to print a tree.

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

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet2.c anasynt.c -o test
$ ./test
```

### **RESULT:**

![](D:\plt\src\anasyntRes.jpg)

## Part3 Analyse sémantique et compilation des fonctions du processeur

This part we write a function find to get the CFA of a lexeme in the LAC.

All the code is in the folder **anasem**.

### **FUNCTION**:

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

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet3.c find.c -o test
$ ./test
```

### **RESULT:**

<img src="D:\plt\src\res3.jpg" style="zoom:130%;" />



## Part4 Interprétation

In this section we will compute the suffix expressions. All the code is in the folder **itrp**.

### **DATA STRUCTURE STACK:**

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

### **FUNCTIONS:**

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

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
$ gcc projet4.c interpret.c ../library/stack.c -o test
$ ./test
```

### **RESULT:**

<img src="D:\plt\src\res5.jpg" style="zoom:130%;" />







