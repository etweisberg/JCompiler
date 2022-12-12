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
    int if_count = 0;
    int while_count = 0;

    // iterating through tokens
    while (next_token(input, &output_t))
    {
        stack_to_asm(asm_output, output_t, &defining_func, &branch_count, &if_count, &while_count);
        if (output_t.type == IF)
        {
            while (next_token(input, &output_t))
            {
                if (output_t.type == ELSE)
                {
                    had_else = true;
                    fprintf(asm_output, "\tJMP ENDIF_%d\n", if_count - 1);
                    fprintf(asm_output, "ELSE_%d\n", if_count - 1);
                    break;
                }
                else if (output_t.type == ENDIF)
                {
                    if (!had_else)
                    {
                        fprintf(asm_output, "ELSE_%d\n", if_count - 1);
                        fprintf(asm_output, "\tENDIF_%d\n", if_count - 1);
                    }
                    else
                    {
                        fprintf(asm_output, "ENDIF_%d\n", if_count - 1);
                    }
                    if_count--;
                    break;
                }
                else
                {
                    stack_to_asm(asm_output, output_t, &defining_func, &branch_count, &if_count, &while_count);
                }
            }
        }
        else if (output_t.type == WHILE)
        {
            if (output_t.type == ENDWHILE)
            {
                if (while_count > 0)
                {
                    fprintf(asm_output, "\tADD R6, R6, #1\n");
                    fprintf(asm_output, "\tLDR R0, R6, #-1\n");
                    fprintf(asm_output, "\tBRnp WHILE_%d\n", while_count);
                    fprintf(asm_output, "ENDWHILE_%d\n", while_count);
                    fprintf(asm_output, "\tJMP WHILE_%d\n", while_count - 1);
                }
                else
                {
                    fprintf(asm_output, "\tADD R6, R6, #1\n");
                    fprintf(asm_output, "\tLDR R0, R6, #-1\n");
                    fprintf(asm_output, "\tBRnp WHILE_%d\n", while_count);
                    fprintf(asm_output, "ENDWHILE_%d\n", while_count);
                }
                break;
            }
            else
            {
                stack_to_asm(asm_output, output_t, &defining_func, &branch_count, &if_count, &while_count);
            }
        }
        print_token(output_t);
        printf("IF_COUNT: %d, WHILE_COUNT: %d\n", if_count, while_count);
    }

    // freeing memory
    fclose(input);
    fclose(asm_output);
}