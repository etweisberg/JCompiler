#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef TOKEN_H_
#include "token.h"
#endif
#ifndef HW7_DEQUE_H_
#include "Deque.h"
#endif

int main(int argc, char **argv)
{
    // file setup
    char name[strlen(argv[1])];
    strcpy(name, argv[1]);
    name[strlen(name) - 2] = '\0';
    FILE *input = fopen(argv[1], "r");
    FILE *test = fopen("test.txt", "w");
    FILE *asm_output = fopen(strcat(name, ".asm"), "w");
    token output_t;
    bool defining_func = false;
    fprintf(asm_output, "\t.CODE\n\t.FALIGN\n");

    // if stack (add when encountering if, pop when encountering endif)
    Deque *if_stack = Deque_Allocate();
    // else stack (add when encountering else, pop when encountering endif)
    Deque *else_stack = Deque_Allocate();
    // while stack (add when encountering while, pop when encountering endwhile)
    Deque *while_stack = Deque_Allocate();

    // iterating through tokens
    while (next_token(input, &output_t))
    {
        stack_to_asm(asm_output, output_t, &defining_func);
        print_token(test, output_t);
    }

    // freeing memory
    fclose(input);
    fclose(test);
    fclose(asm_output);
    Deque_Free(if_stack);
    Deque_Free(else_stack);
    Deque_Free(while_stack);
}