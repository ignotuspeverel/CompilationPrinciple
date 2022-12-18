#include <stdbool.h>
#include "anasynt.h"

bool translate(char* s, char buffer[], number location[], int* bufferLen)
{
    if(s == "") 
    {
        printf("no input please check\n");
        return 2;
    }
    bool isInteger = false;
    int bufferLength = 0; 
    int loc = 0;
    int length = strlen(s);
    for(int i = 0; i < length; i++)
    {
        if(s[i] == '(')
        {
            if(isInteger) location[loc].endptr = i-1;
            
            isInteger = false;
            buffer[bufferLength] = 'O';
            bufferLength++;
        }
        else if(s[i] == ')')
        {
            if(isInteger) location[loc].endptr = i-1;
            isInteger = false;
            buffer[bufferLength] = 'F';
            bufferLength++;
        }
        else if(s[i] == 'x')
        {
            if(isInteger) location[loc].endptr = i-1;
            isInteger = false;
            buffer[bufferLength] = 'H';
            bufferLength++;
        }
        else if(s[i] == '+')
        {
            if(isInteger) location[loc].endptr = i-1;
            isInteger = false;
            buffer[bufferLength] = 'P';
            bufferLength++;
        }
        else if(s[i] == '-')
        {
            if(isInteger) location[loc].endptr = i-1;
            isInteger = false;
            buffer[bufferLength] = 'M';
            bufferLength++;
        }
        else if(s[i] == '0' || s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9'){
            if(!isInteger){
                if (s[i] == '0') return false;
                buffer[bufferLength] = 'N';
                location[bufferLength].startptr = i;
                loc = bufferLength;
                bufferLength++;
            }
            isInteger = true; 
        }
        else if(s[i] == ' ') continue;
        else{
            return false;
        } 
    }
    *bufferLen = bufferLength;
    return true;
}

tree assemble(char* name, tree left, tree right)
{
    int len = strlen(name);
    tree newTree = malloc(sizeof(struct node));
    newTree->label = malloc(sizeof(char)*(len+2));
    strcpy(newTree->label, name);
    newTree -> lc = left;
    newTree -> rc = right;
    return newTree;
}

tree factD(int sptr, int eptr, char* s, char* origin, number location[])
{
    if (( sptr == eptr && s[sptr]=='N')){
        int startptr = location[sptr].startptr; int endptr = location[sptr].endptr;
        char content[endptr-startptr + 2];
        for(int i = 0; i < endptr - startptr+1 ; i++) content[i] = origin[startptr + i];
        content[endptr-startptr+1] = '\0';
        return assemble(content, NULL, NULL);
    }
    if (s[sptr]=='O' && s[eptr]=='F')
        return term(sptr+1, eptr-1, s, origin, location);
  return NULL;
}


tree fact(int sptr, int eptr, char* s, char* origin, number location[])
{
    tree lc, rc;
    rc = factD(sptr, eptr, s, origin, location);
    if(rc != NULL) return rc;
    int i = eptr - 1;
    while (i > sptr) 
    {
        if(s[i] == 'H')
        {
            rc = factD(i+1, eptr, s, origin, location);
            lc = fact(sptr, i-1, s, origin, location);
            if (rc != NULL && lc != NULL) return assemble("x", lc, rc);
        }
        i--;
    }
    return NULL;
}

tree term(int sptr, int eptr, char* s, char* origin, number location[])
{
    tree lc, rc;
    rc = fact(sptr, eptr, s, origin, location);
    if(rc != NULL) return rc;
    int i = eptr - 1;

    while (i > sptr)
    {
        if(s[i] == 'P')
        {
            rc = fact(i+1, eptr, s, origin, location);
            lc = term(sptr, i-1, s, origin, location);
            if (rc != NULL && lc != NULL) return assemble("+", lc, rc);
        }
        if(s[i] == 'M')
        {
            rc = fact(i+1, eptr, s, origin, location);
            lc = term(sptr, i-1, s, origin, location);
            if (rc != NULL && lc != NULL) return assemble("-", lc, rc);
        }
        i--;
    }

    if (i == sptr && s[i] == 'M')
    {
        rc =  fact(i+1, eptr, s, origin, location);
        if(rc != NULL) { return assemble("-", NULL, rc);}
    }
    return NULL;
}

void printTree(tree tr, int blank)
{
    if (tr == NULL) return;
    int len = strlen(tr->label);
    printTree(tr->lc, blank + len + 1);
    for (int i = 0; i < blank; i++) printf(" ");
    printf("%s\n", tr->label);
    printTree(tr->rc, blank + len + 1);
}


