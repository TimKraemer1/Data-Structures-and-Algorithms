//Tim Kraemer
//CruzID: tikraeme
//pa1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string.h>

#include "List.h"

#define MAX_LEN 4096;

int main(int argc, char* argv[]) {
    //check number of arguements
    if (argc != 3) {
        fprintf(stderr, "Lex Error: Invalid number of input arguements\n");
        return -1;
    }

    int l_count = 0;

    //opening files and checking if they are opened correctly
    FILE* in_fp = fopen(argv[1], "r");
    if(in_fp == NULL) {
        fprintf(stderr, "Lex Error: Unable to open input file\n");
        return -1;
    }
    FILE* out_fp = fopen(argv[2], "w");
    if(out_fp == NULL) {
        fprintf(stderr, "Lex Error: Unable to open output file\n");
    }

    //count number of lines in the input file
    char c = getc(in_fp);
    while(c != EOF) {
        if(c == '\n') {l_count++;}
        c = getc(in_fp);
    }

    fseek(in_fp, 0, SEEK_SET);

    char buf[301];
    
    //allocate line array, and read in each line and store it in the array
    char** line_array = calloc(l_count, sizeof(char*));
    for(int i = 0; i < l_count; i++) {
        fgets(buf, 301, in_fp);
        buf[strlen(buf)-1] = '\0';
        char* new_line = calloc(strlen(buf)+1, sizeof(char));
        strcpy(new_line, buf);
        line_array[i] = new_line;
    }

    fclose(in_fp);

    //compare lines and then insert their indexes alphabetically in the List
    List sorting_list = newList();
    append(sorting_list, 0);
    for(int i = 1; i < l_count; i++) {
        moveFront(sorting_list);
        for(int j = 0; j < length(sorting_list); j++) {
            if(strcmp(line_array[i], line_array[get(sorting_list)]) <= 0) {
                insertBefore(sorting_list, i);
                break;
            }
            moveNext(sorting_list);
        }
        if(index(sorting_list) == -1) {
            append(sorting_list, i);
        }
    }

    //print the lines in the order of the indexes
    moveFront(sorting_list);
    while(index(sorting_list) != -1) {
        fprintf(out_fp, "%s\n", line_array[get(sorting_list)]);
        moveNext(sorting_list);
    }
    fclose(out_fp);

    //free memory
    freeList(&sorting_list);
    for(int i = 0; i < l_count; i++) {
	free(line_array[i]);
    }
    free(line_array);
}

