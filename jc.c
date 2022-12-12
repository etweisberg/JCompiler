#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "Deque.h"

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
    bool had_else = false;
    int branch_count = 0;

    // if stack (add when encountering if, pop when encountering endif)
    Deque *if_stack = Deque_Allocate();
    int if_count = 0;
    // else stack (add when encountering else, pop when encountering endif)
    Deque *else_stack = Deque_Allocate();
    int else_count = 0;
    // while stack (add when encountering while, pop when encountering endwhile)
    Deque *while_stack = Deque_Allocate();
    int while_count = 0;

    // iterating through tokens
    while (next_token(input, &output_t))
    {
        Deque_Peek_Front(if_stack, &if_count);
        Deque_Peek_Front(else_stack, &else_count);
        Deque_Peek_Front(while_stack, &while_count);
        stack_to_asm(asm_output, output_t, &defining_func, &had_else, &branch_count, &if_count, &else_count, &while_count);
        if (output_t.type == IF)
        {
            Deque_Push_Front(if_stack, if_count + 1);
        }
        else if (output_t.type == ELSE)
        {
            had_else = true;
            Deque_Push_Front(else_stack, else_count + 1);
        }
        else if (output_t.type == WHILE)
        {
            Deque_Push_Front(while_stack, while_count + 1);
        }
        else if (output_t.type == ENDIF)
        {
            if (had_else)
            {
                had_else = false;
                Deque_Pop_Front(if_stack, &if_count);
                Deque_Pop_Front(else_stack, &else_count);
            }
            else
            {
                Deque_Pop_Front(if_stack, &if_count);
            }
        }
        else if (output_t.type == ENDWHILE)
        {
            Deque_Pop_Front(while_stack, &while_count);
        }
        print_token(output_t);
        printf("IF_COUNT: %d, ELSE_COUNT: %d, WHILE_COUNT: %d\n", if_count, else_count, while_count);
    }

    // freeing memory
    fclose(input);
    fclose(asm_output);
    Deque_Free(if_stack);
    Deque_Free(else_stack);
    Deque_Free(while_stack);
}