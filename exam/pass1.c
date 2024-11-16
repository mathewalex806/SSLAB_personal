#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void main()
{
    char label[10], opcode[10], operand[10];
    int locctr;
    FILE *symtab , *optab, *input, *intermediate;
    symtab = fopen("symtab.txt","w");
    optab = fopen("optab.txt","r");
    input = fopen("input.txt","r");
    intermediate = fopen("intermediate.txt","w");
}