
#include <stdbool.h>
#include "analex.h"
#define STATE_COMMENT 1
#define STATE_STRING 2
#define STATE_INT 3
#define STATE_MOT 4


/**
   @brief lexique analysis of a file
   @param FILE and a queue to store the result of the lexique
 */
bool lex_analyse(FILE *file, queue *q) {
    int bufferLength = 0;
    regex_t reg_compile_comment;
    regex_t reg_compile_int;
    regex_t reg_compile_mot;
    regex_t reg_compile_string;
    regmatch_t result;
    //open the file
    if ((file == NULL)) {
        perror("Error getting the file");
        regfree(&reg_compile_comment);
        regfree(&reg_compile_string);
        regfree(&reg_compile_int);
        regfree(&reg_compile_mot);
        return false;
    }

    if (regcomp(&reg_compile_comment, REGEX_COMMENT, REG_EXTENDED | REG_NEWLINE)) {
        perror("Regex invalide");
        regfree(&reg_compile_comment);
        return false;
    }

    if (regcomp(&reg_compile_string, REGEX_STRING, REG_EXTENDED | REG_NEWLINE)) {
        perror("Regex invalide");
        regfree(&reg_compile_string);
        return false;
    }

    if (regcomp(&reg_compile_int, REGEX_INTEGER, REG_EXTENDED | REG_NEWLINE)) {
        perror("Regex invalide");
        regfree(&reg_compile_int);
        return false;
    }

    if (regcomp(&reg_compile_mot, REGEX_IDENTIFIER, REG_EXTENDED | REG_NEWLINE)) {
        perror("Regex invalide");
        regfree(&reg_compile_mot);
        return false;
    }
    
    //read file to buffer
    while(1) {    
		char ch = fgetc(file);
		if (ch == EOF) break;
		bufferLength++;  
	}
    char buffer[bufferLength];                      //create the buffer 
    int match_check[bufferLength];                  //create the check buffer
    memset(match_check, 0, sizeof(match_check));    //all set to 0
    rewind(file);
    int count = 0 ;
    for (int i = 0; i < bufferLength; i++) {
        char ch = fgetc(file);
        buffer[i] = ch;
    }

    //match the cotent, we use a match_check[] to declare the type of char in the same location of buffer[]
    for(int i = 0; regexec(&reg_compile_comment, buffer + i, 1, &result, 0) != REG_NOMATCH; i += result.rm_eo) {
        for (int j = i+result.rm_so; j < i + result.rm_eo; j ++ ) {
            match_check[j] = STATE_COMMENT;
        }
    }

    for(int i = 0; regexec(&reg_compile_string, buffer + i, 1, &result, 0) != REG_NOMATCH; i += result.rm_eo) {
        if (match_check[i+result.rm_so] == 0){
            for (int j = i+result.rm_so; j < i + result.rm_eo; j ++) 
                match_check[j] = STATE_STRING;
        }
    }

    for(int i = 0; regexec(&reg_compile_int, buffer + i, 1, &result, 0) != REG_NOMATCH; i += result.rm_eo) {
        if (match_check[i+result.rm_so] == 0){
            for (int j = i+result.rm_so; j < i + result.rm_eo; j ++) 
                match_check[j] = STATE_INT;
        }
    }

    for(int i = 0; regexec(&reg_compile_mot, buffer + i, 1, &result, 0) != REG_NOMATCH; i += result.rm_eo) {
        if (match_check[i+result.rm_so] == 0){
            for (int j = i + result.rm_so; j < i + result.rm_eo; j++){
                if (j < bufferLength) 
                    match_check[j] = STATE_MOT;
            }             
        }
    }

    //put each content to the queue
    int start_ptr, end_ptr = 0;
    lexique lex;
    while (start_ptr <= bufferLength) {
        if ((match_check[start_ptr] == 0) || (match_check[start_ptr] == 1)) start_ptr++;
        else{
            end_ptr = start_ptr;
            while (match_check[end_ptr] != 0 && match_check[end_ptr] != 1) end_ptr++;
        
            switch (match_check[start_ptr])
            {
            case STATE_INT:
                lex.type = INT;
                lex.start = start_ptr;
                lex.end = end_ptr - 2;
                break;

            case STATE_MOT:
                lex.type = MOTS;
                lex.start = start_ptr;
                lex.end = end_ptr - 1;
                break;

            case STATE_STRING:
                lex.type = STRING;
                lex.start = start_ptr;
                lex.end = end_ptr - 1;
                break;

            default:
                break;
            }
            start_ptr = end_ptr + 1;
            queue_push_back(q, &lex, sizeof(lex));
        }
    }

    display_queue(buffer, q);

    regfree(&reg_compile_comment);
    regfree(&reg_compile_string);
    regfree(&reg_compile_int);
    regfree(&reg_compile_mot);

    return true;
}

/**
   @brief Enqueue element at the end of queue
   @param char buffer[] of input, and a queue that stores the result
 */
void display_queue(char buffer[], queue *q){
    printf("\n--------------Result-------------------\n");
    lexique lex;
    q_node *temp = q->front;
    for (int i = 0; i < q->size; i++){
        lex = *(lexique* )temp->element;
        //get the output for a tyypical lexique and change the '\n' to '\\n'
        int count_change_line = 0;
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            char ch = buffer[lex.start + i];
            if (ch == '\n') count_change_line++;     
        }
        int output_size = (lex.end - lex.start) + 1 + count_change_line;
        char output[output_size];
        int j = 0;
        for (int i = 0; i < lex.end - lex.start + 1; i++){
            char ch = buffer[lex.start + i];
            if (ch != '\n')  output[j] = buffer[lex.start + i];
            else{
                output[j] = '\\';
                output[j+1] = 'n';
                j++;
            }
            j++;
        }
        //output the result
        if (i == q->size -1) {
            switch (lex.type)
            {
            case INT:
                printf("N(%.*s)\n", j, output);
                break;
            case MOTS:
                printf("M(\"%.*s\")\n", j, output);
                break;
            case STRING:
                printf("S(\"%.*s)\n", j-2, output + 2);
                break;
            default:
                break;
            }
        }
        else{
            switch (lex.type)
            {
            case INT:
                printf("N(%.*s)->", j, output);
                break;
            case MOTS:
                printf("M(\"%.*s\")->", j, output);
                break;
            case STRING:
                printf("S(\"%.*s)->", j-2, output + 2);
                break;
            default:
                break;
            }
        }
        temp = temp->next;
    }
    printf("---------------end---------------------\n\n");
}