#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "token.h"

bool next_token(FILE *j_file, token *output)
{
    char j_token[MAX_TOKEN_LENGTH + 1];
    if (fscanf(j_file, "%s", j_token) == 1)
    {
        // ignoring comments
        while (strcmp(j_token, ";;") == 0 || strcmp(j_token, ";") == 0)
        {
            int c;
            c = fgetc(j_file);
            while (c != '\n')
            {
                c = fgetc(j_file);
            }
            fscanf(j_file, "%s", j_token);
        }
        if (strstr(j_token, "0x") != NULL)
        {
            output->type = LITERAL;
            sscanf(j_token, "%x", &(output->literal_value));
        }
        else if (sscanf(j_token, "%d", &(output->literal_value)) == 1)
        {
            output->type = LITERAL;
        }
        else
        {
            if (strcmp(j_token, "+") == 0)
            {
                output->type = PLUS;
            }
            else if (strcmp(j_token, "-") == 0)
            {
                output->type = MINUS;
            }
            else if (strcmp(j_token, "*") == 0)
            {
                output->type = MUL;
            }
            else if (strcmp(j_token, "/") == 0)
            {
                output->type = DIV;
            }
            else if (strcmp(j_token, "%") == 0)
            {
                output->type = MOD;
            }
            else if (strcmp(j_token, "and") == 0)
            {
                output->type = AND;
            }
            else if (strcmp(j_token, "or") == 0)
            {
                output->type = OR;
            }
            else if (strcmp(j_token, "not") == 0)
            {
                output->type = NOT;
            }
            else if (strcmp(j_token, "lt") == 0)
            {
                output->type = LT;
            }
            else if (strcmp(j_token, "le") == 0)
            {
                output->type = LE;
            }
            else if (strcmp(j_token, "eq") == 0)
            {
                output->type = EQ;
            }
            else if (strcmp(j_token, "ge") == 0)
            {
                output->type = GE;
            }
            else if (strcmp(j_token, "gt") == 0)
            {
                output->type = GT;
            }
            else if (strcmp(j_token, "if") == 0)
            {
                output->type = IF;
            }
            else if (strcmp(j_token, "else") == 0)
            {
                output->type = ELSE;
            }
            else if (strcmp(j_token, "endif") == 0)
            {
                output->type = ENDIF;
            }
            else if (strcmp(j_token, "while") == 0)
            {
                output->type = WHILE;
            }
            else if (strcmp(j_token, "endwhile") == 0)
            {
                output->type = ENDWHILE;
            }
            else if (strcmp(j_token, "drop") == 0)
            {
                output->type = DROP;
            }
            else if (strcmp(j_token, "dup") == 0)
            {
                output->type = DUP;
            }
            else if (strcmp(j_token, "swap") == 0)
            {
                output->type = SWAP;
            }
            else if (strcmp(j_token, "rot") == 0)
            {
                output->type = ROT;
            }
            else if (strcmp(j_token, "return") == 0)
            {
                output->type = RETURN;
            }
            else if (strcmp(j_token, "defun") == 0)
            {
                output->type = DEFUN;
            }
            else if (strstr(j_token, "arg") != NULL)
            {
                output->type = ARG;
                memmove(&j_token[0], &j_token[0 + 1], strlen(j_token) - 0);
                memmove(&j_token[0], &j_token[0 + 1], strlen(j_token) - 0);
                memmove(&j_token[0], &j_token[0 + 1], strlen(j_token) - 0);
                output->arg_no = atoi(j_token);
            }
            else
            {
                output->type = IDENT;
                strcpy(output->str, j_token);
            }
        }
        return true;
    }
    // cannot read a character from the file
    else
    {
        return false;
    }
}

void print_token(token to_print)
{
    switch (to_print.type)
    {
    case PLUS:
        printf(" + \n");
        break;
    case MINUS:
        printf(" - \n");
        break;
    case MUL:
        printf(" * \n");
        break;
    case DIV:
        printf(" / \n");
        break;
    case MOD:
        printf(" %% \n");
        break;
    case AND:
        printf(" and \n");
        break;
    case OR:
        printf(" or \n");
        break;
    case NOT:
        printf(" not \n");
        break;
    case LT:
        printf(" lt \n");
        break;
    case LE:
        printf(" le \n");
        break;
    case EQ:
        printf(" eq \n");
        break;
    case GE:
        printf(" ge \n");
        break;
    case GT:
        printf(" gt \n");
        break;
    case IF:
        printf(" if \n");
        break;
    case ELSE:
        printf(" else \n");
        break;
    case ENDIF:
        printf(" endif \n");
        break;
    case WHILE:
        printf(" while \n");
        break;
    case ENDWHILE:
        printf(" endwhile \n");
        break;
    case DROP:
        printf(" drop \n");
        break;
    case DUP:
        printf(" dup \n");
        break;
    case SWAP:
        printf(" swap \n");
        break;
    case ROT:
        printf(" rot \n");
        break;
    case RETURN:
        printf(" return \n");
        break;
    case DEFUN:
        printf(" defun \n");
        break;
    case IDENT:
        printf(" %s \n", to_print.str);
        break;
    case ARG:
        printf(" arg%d \n", to_print.arg_no);
        break;
    case LITERAL:
        printf(" %d \n", to_print.literal_value);
        break;
    default:
        break;
    }
}

void stack_to_asm(FILE *asm_file, token to_write, bool *defining_func, int *branch_count, int *if_count, int *while_count)
{
    switch (to_write.type)
    {
    case LITERAL:;
        int const_val = to_write.literal_value & 0x00FF;
        uint16_t hiconst_val = (to_write.literal_value & 0xFF00) >> 8;
        printf("%d\n", (const_val & 0xFF) | (hiconst_val << 8));
        fprintf(asm_file, "\tCONST R0, #%d\n", const_val);
        fprintf(asm_file, "\tHICONST R0, #%d\n", hiconst_val);
        fprintf(asm_file, "\tADD R6, R6, #-1\n");
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        break;
    // if u read in defun check next token for ident
    case DEFUN:
        if (*defining_func == false)
        {
            *defining_func = true;
        }
        else
        {
            perror("DEFUN BAD ORDER");
        }
        break;
    case IDENT:
        if (*defining_func)
        {
            *defining_func = false;
            // make new label and stack frame
            // function prologue
            fprintf(asm_file, ".CODE\n.FALIGN\n");
            fprintf(asm_file, "%s\n", to_write.str);
            fprintf(asm_file, "\tSTR R7, R6, #-2\n"); // save return address
            fprintf(asm_file, "\tSTR R5, R6, #-3\n"); // save base pointer
            fprintf(asm_file, "\tADD R6, R6, #-3\n");
            fprintf(asm_file, "\tADD R5, R6, #0\n"); // update frame pointer
        }
        else
        {
            // jump to old label
            fprintf(asm_file, "\tJSR %s\n", to_write.str);
            fprintf(asm_file, "\tADD R6, R6, #-1\n");
        }
        break;
    case RETURN:
        // function epilogue
        fprintf(asm_file, "\tLDR R7, R6, #0\n"); // saving return value
        fprintf(asm_file, "\tADD R6, R5, #0\n"); // popping locals
        fprintf(asm_file, "\tADD R6, R6, #3\n");
        fprintf(asm_file, "\tSTR R7, R6, #-1\n"); // store return value
        fprintf(asm_file, "\tLDR R5, R6, #-3\n"); // restore frame pointer
        fprintf(asm_file, "\tLDR R7, R6, #-2\n"); // restore return address
        fprintf(asm_file, "\tRET\n");
        break;
    case PLUS:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case MUL:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tMUL R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case MINUS:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tSUB R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case DIV:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tDIV R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case MOD:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tMOD R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case AND:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tAND R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case OR:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tOR R1, R1, R0\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case NOT:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tNOT R0, R0\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case ARG:
        fprintf(asm_file, "\tADD R0, R5, #2\n");
        fprintf(asm_file, "\tLDR R0, R0, #%d\n", to_write.arg_no);
        fprintf(asm_file, "\tSTR R0, R6, #-1\n");
        fprintf(asm_file, "\tADD R6, R6, #-1\n");
        break;
    case IF:
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tLDR R0, R6, #-1\n");
        fprintf(asm_file, "\tBRz ELSE_%d\n", *if_count);
        *if_count = *if_count + 1;
        break;
        /*
         * 1. the stuff u have above + if_num++;
         * 2. while(next_token)
         *   2.1. if the token is not ELSE or ENDIF, call stack_to_asm
         *   2.2. otherwise, handle else and endif accordingly by copying their bodies below
         *
         */
    case WHILE:
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tLDR R0, R6, #-1\n");
        fprintf(asm_file, "\tBRz ENDWHILE_%d\n", *while_count);
        fprintf(asm_file, "WHILE_%d\n", *while_count);
        *while_count = *while_count + 1;
        break;
    case LT:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tCMP R0, R1\n");
        fprintf(asm_file, "\tBRzp, FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #1\n");
        fprintf(asm_file, "\tJMP, END_%d\n", *branch_count);
        fprintf(asm_file, "FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #0\n");
        fprintf(asm_file, "END_%d\n", *branch_count);
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        *branch_count += 1;
        break;
    case LE:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tCMP R0, R1\n");
        fprintf(asm_file, "\tBRp, FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #1\n");
        fprintf(asm_file, "\tJMP, END_%d\n", *branch_count);
        fprintf(asm_file, "FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #0\n");
        fprintf(asm_file, "END_%d\n", *branch_count);
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        *branch_count += 1;
        break;
    case EQ:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tCMP R0, R1\n");
        fprintf(asm_file, "\tBRnp, FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #1\n");
        fprintf(asm_file, "\tJMP, END_%d\n", *branch_count);
        fprintf(asm_file, "FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #0\n");
        fprintf(asm_file, "END_%d\n", *branch_count);
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        *branch_count += 1;
        break;
    case GE:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tCMP R0, R1\n");
        fprintf(asm_file, "\tBRn, FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #1\n");
        fprintf(asm_file, "\tJMP, END_%d\n", *branch_count);
        fprintf(asm_file, "FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #0\n");
        fprintf(asm_file, "END_%d\n", *branch_count);
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        *branch_count += 1;
        break;
    case GT:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        fprintf(asm_file, "\tCMP R0, R1\n");
        fprintf(asm_file, "\tBRnz, FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #1\n");
        fprintf(asm_file, "\tJMP, END_%d\n", *branch_count);
        fprintf(asm_file, "FALSE_%d\n", *branch_count);
        fprintf(asm_file, "\tCONST R0, #0\n");
        fprintf(asm_file, "END_%d\n", *branch_count);
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        *branch_count += 1;
        break;
    case DROP:
        fprintf(asm_file, "\tADD R6, R6, #1\n");
        break;
    case DUP:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tADD R6, R6, #-1\n");
        fprintf(asm_file, "\tSTR R0, R6, #0\n");
        break;
    case SWAP:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tSTR R0, R6, #1\n");
        fprintf(asm_file, "\tSTR R1, R6, #0\n");
        break;
    case ROT:
        fprintf(asm_file, "\tLDR R0, R6, #0\n");
        fprintf(asm_file, "\tLDR R1, R6, #1\n");
        fprintf(asm_file, "\tLDR R2, R6, #2\n");
        fprintf(asm_file, "\tSTR R0, R6, #1\n");
        fprintf(asm_file, "\tSTR R2, R6, #0\n");
        fprintf(asm_file, "\tSTR R1, R6, #2\n");
        break;
    default:
        break;
    }
}