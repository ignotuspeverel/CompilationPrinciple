#include "find.h"

/*
   @brief find the cfa by LAC
   @param LAC, length of the Lac, origin file, the input lexeme
*/
int find(int lac[], int length, char* origin, lexique lex){
    //a pointer to read, the length of a mots in the LAC, cfa result
    int readPtr = 1, readLen = 0, cfa = 0;

    //check the LAC
    if (lac[0] != 0){
        printf("Error LAC input");
        return -1;
    }
    if(length == 1){
        return -1;
    }

    //initialization
    readLen = lac[1];
    int startPtr = lex.start; 
    bool flag = false;

    //read the LAC
    while(readPtr < length){
        readLen = lac[readPtr];
        for (int i = 1; i <= readLen; i++){
            if ((int)origin[startPtr + i - 1] != lac[readPtr + i]) break;
            if ((int)origin[startPtr + i - 1] == lac[readPtr + i] && i == readLen) flag = true;
        }
        if (flag){
            cfa = lac[readPtr + readLen + 1];
            return cfa;
        }
        else 
            readPtr += (readLen + 3);
    }
    if (!flag) 
        return -2;

};