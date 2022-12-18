#include <stdio.h>
#include <stdlib.h>

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
        exit(EXIT_FAILURE);
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
        input_array[i] = new_word;
    }

    fclose(in_fp);
    for(int i = 0; i < line_count; i++) {
        printf("%s\n", input_array[i]);
    }
    
    //freeing list
    for(int i = 0; i < line_count; i++) {
        free(input_array[i]);
    }
    free(input_array);
}