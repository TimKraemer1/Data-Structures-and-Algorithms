#include <stdio.h>
#include <stdlib.h>

#include "List.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Error: Expected 2 arguements (input and output file)\n");
        exit(EXIT_FAILURE);
    }
}