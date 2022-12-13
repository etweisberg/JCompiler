#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

int main(int argc, char **argv)
{
    // file setup
    char name[strlen(argv[1])];
    strcpy(name, argv[1]);
    name[strlen(name) - 2] = '\0';
    FILE *input = fopen(argv[1], "r");
    FILE *asm_output = fopen(strcat(name, ".asm"), "w");

    // state variables
    token output_t;
    bool defining_func = false;
    int branch_count = 0;
    int if_count = 0;
    int while_count = 0;

    // iterating through tokens
    while (next_token(input, &output_t))
    {
        stack_to_asm(input, asm_output, output_t, &defining_func, &branch_count, &if_count, &while_count);
    }

    // freeing memory
    fclose(input);
    fclose(asm_output);
}