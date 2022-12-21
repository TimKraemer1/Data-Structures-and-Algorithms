#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

int main(int argc, char* argv[]) {

    if(argc != 3) {
        fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
        exit(EXIT_FAILURE);
    }

    int line_count = 0;
    FILE* in_fp = fopen(argv[1], "r");

    if(in_fp == NULL){
        printf("IO Error: Could not open file %s\n", argv[1]);
        return -1;    
        }
    for(char c = getc(in_fp); c != EOF; c = getc(in_fp)) {
        if(c == '\n') {
            line_count++;
        }
    }
    fseek(in_fp, 0, SEEK_SET);

    char** input_array = calloc(line_count, sizeof(char*));

    int string_length = 100;
    for(int i = 0; i < line_count; i++) {
        char* new_word = malloc(sizeof(char) * string_length);
        fgets(new_word, string_length, in_fp);
        new_word[strlen(new_word)-1] = '\0';
        input_array[i] = new_word;
    }

    fclose(in_fp);
    
    List word_list = newList();

    for(int i = 0; i < line_count; i++) {
        if(length(word_list) == 0) {
            append(word_list, i);
            moveFront(word_list);
        }
        else {
            for(int j=0; j < length(word_list); j++) {
                if(strcmp(input_array[i], input_array[get(word_list)]) <= 0) {
                    insertBefore(word_list, i);
                    break;
                }
                moveNext(word_list);
            }
            //check to see if we already inserted the current index anywhere in the list earlier
            if(index(word_list) == -1) {
                append(word_list, i);
            }
            moveFront(word_list);
        }
    }

    FILE* out_fp = fopen(argv[2], "w");
    moveFront(word_list);
    while(index(word_list) != -1) {
        fprintf(out_fp, "%s\n", input_array[get(word_list)]);
        moveNext(word_list);
    }

    fclose(out_fp);

    //freeing linked list
    freeList(&word_list);

    //freeing word array
    for(int i = 0; i < line_count; i++) {
        free(input_array[i]);
    }
    free(input_array);
}