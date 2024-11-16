#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WORD_SIZE 3
#define RESW_FACTOR 3

void main()
{
    char opcode[10], label[10], operand[10], code[10], mnemonic[10];
    int locctr, start;
    FILE *input, *inter, *optab, *symtab, *symsearch;
    bool flag = true;
    bool found = false;

    input = fopen("input.txt", "r");
    inter = fopen("inter.txt", "w");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    symsearch = fopen("symtab.txt", "r");

    if (input != NULL && inter != NULL && optab != NULL && symtab != NULL)
    {
        printf("All files opened.\n");
    }

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0)
    {
        fseek(input, SEEK_SET, 0);
        fscanf(input, "%s\t%s\t%X", label, opcode, &start);
        locctr = start;
        fprintf(inter, "-\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    else
    {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0)
    {
        found = false;  // Reset flag
        fprintf(inter, "%X\t", locctr);

        if (strcmp(label, "-") != 0)
        {
            char symbol[10], loc[10];
            fseek(symsearch, 0, SEEK_SET);
            while (fscanf(symsearch, "%s\t%s", symbol, loc) == 2)
            {
                if (strcmp(symbol, label) == 0)
                {
                    printf("Duplicate label found: %s\n", label);
                    exit(0);
                }
            }
            fprintf(symtab, "%s\t%X\n", label, locctr);
        }

        fseek(optab, 0, SEEK_SET);
        while (fscanf(optab, "%s\t%s", code, mnemonic) == 2)
        {
            if (strcmp(code, opcode) == 0)
            {
                locctr += WORD_SIZE;
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                locctr += WORD_SIZE;
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                if (operand[0] == 'C')
                    locctr += strlen(operand) - 3;
                else if (operand[0] == 'X')
                    locctr += (strlen(operand) - 3) / 2;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += RESW_FACTOR * atoi(operand);
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += atoi(operand);
            }
            else
            {
                printf("Invalid OP code: %s\n", opcode);
                fprintf(inter, "ERROR\t%s\t%s\t%s\n", label, opcode, operand);
            }
        }

        fprintf(inter, "%s\t%s\t%s\n", label, opcode, operand);
        if (fscanf(input, "%s\t%s\t%s", label, opcode, operand) != 3)
        {
            printf("Error reading input file.\n");
            break;
        }
    }

    fprintf(inter, "-\t%s\t%s\t%s\n", label, opcode, operand);
    fclose(input);
    fclose(symsearch);
    fclose(symtab);
    fclose(inter);
    fclose(optab);
    printf("END OF PROGRAM.\n");
}
