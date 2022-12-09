#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

int main(int argc, char **argv)
{
    char name[strlen(argv[1])];
    strcpy(name, argv[1]);
    name[strlen(name) - 2] = '\0';
    FILE *input = fopen(argv[1], "r");
    FILE *test = fopen("test.txt", "w");
    FILE *asm_output = fopen(strcat(name, ".asm"), "w");
    token output_t;
    bool defining_func = false;
    fprintf(asm_output, "\t.CODE\n\t.FALIGN\n");
    while (next_token(input, &output_t))
    {
        stack_to_asm(asm_output, output_t, &defining_func);
        print_token(test, output_t);
    }
    fclose(input);
    fclose(test);
    fclose(asm_output);
}