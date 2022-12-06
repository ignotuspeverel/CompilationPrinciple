# PROJECT FOR CS448

## Part1 Analyse lexicale

For this part, I used regular expressions to distinguish between numbers, words and strings.

Here are the regular expressions used:

<img src="D:\plt\src\regexexpr.jpg" style="zoom:67%;" />

In the main function, I read the file to one buffer and use the regular expressions in an order of comment, string, integer and word:

<img src="D:\plt\src\mainfuncLex.jpg" style="zoom:67%;" />

For content that are recognized, I create a struct to store its type, its beginning and ending in the file:

<img src="D:\plt\src\lexstruct.jpg" alt="lexstruct" style="zoom:67%;" />

I also write a queue data structure to store my created structure lexique.

Finally a display function to display them from queue.

**USAGE:**

To test in Linux, use the following code in bash to compile and run:

```bash
gcc projet1.c analex.c ./library/queue.c -o test
./test
```

**RESULT:**

![](D:\plt\src\lexresult.jpg)