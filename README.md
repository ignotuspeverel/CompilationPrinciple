# PROJECT FOR CS448

## Part1 Analyse lexicale

For this part, I used regular expressions to distinguish between numbers, words and strings. All the detailed files are in the folder **analex**.

Here are the regular expressions used:

<img src=".\src\regexexpr.jpg" style="zoom:67%;" />

In the main function, I read the file to one buffer and use the regular expressions in an order of comment, string, integer and word:

<img src=".\src\mainfuncLex.jpg" style="zoom:67%;" />

For content that are recognized, I create a struct to store its type, its beginning and ending in the file:

<img src=".\src\lexstruct.jpg" alt="lexstruct" style="zoom:67%;" />

I also write a queue data structure to store my created structure lexique.

Finally a display function to display them from queue.

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
gcc projet1.c analex.c ../library/queue.c -o test
./test
```

### **RESULT:**

![](.\src\lexresult.jpg)

## Part 2. Analyse syntaxique

For this part, I used a BNF. All the detailed files are in the folder **anasynt**.

The BNF I used is:
$$
<fact>\quad := \quad<factD>\quad | \quad<fact><factD>  \newline
<factD>\quad := \quad N \quad|\quad O <term> F \newline
<term> \quad:= \quad<fact> \quad| \quad<term> P <fact> \quad | \quad<term> M <fact> | \quad M <fact>
$$

| **N**    | **NUMBER**     |
| -------- | -------------- |
| **O, F** | **'(' ,  ')'** |
| **P**    | **'+'**        |
| **M**    | **'-'**        |
| **H**    | **'x'**        |

The whole function is designed based on a recursive idea.

### Functions:

**translate:** to recognize a string and replace it with the symbols above.

**assemble:** to assemble a tree with left child and right child.

**factD:** to recognize a **<factD>.**

**fact:**  to recognize a **<fact>**.

**term:** to recognize a **<term>**.

**printTree:** to print a tree.

### **USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
gcc projet2.c anasynt.c -o test
./test
```

**RESULT:**

