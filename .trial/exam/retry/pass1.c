#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void main()
{
    char label[10], opcode[10], operand[10], code[10], mnemonic[10];
    FILE *input, *symtab, *symsearch, *optab, *inter;
    int locctr, start;
    bool flag = false, opfound = false;

    input = fopen("input.txt","r");
    symtab = fopen("symtab.txt","w");
    inter = fopen("inter.txt","w");
    optab = fopen("optab.txt","r");
    symsearch = fopen("symtab.txt","r");

    if (input!= NULL&&symsearch!= NULL||symtab!= NULL||inter!= NULL||optab!= NULL )
    {
        printf("All files opened successfully\n");
    }
    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    if (strcmp(opcode, "START")==0)
    {
        fseek(input, SEEK_SET, 0);
        fscanf(input,"%s\t%s\t%X",label,opcode,&start);
        locctr = start;
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    }
    else
    {
        locctr =0;
    }
    while(strcmp(opcode, "END")!=0)
    {
        fprintf(inter,"%X\t",locctr);
        //check for labels
        if(strcmp(label,"-")!=0)
        {
            //checking for existing label or duplicated label
            char sym[10], loc[10];
            fseek(symsearch,SEEK_SET,0);
            while(fscanf(symsearch,"%s\t%s",sym, loc)==2)
            {
                if (strcmp(sym, label)==0)
                {
                    printf("Duplicate label found \n.");
                    flag = true;
                    exit(1);
                }
            }
            fprintf(symtab,"%s\t%X\n",label, locctr);
        
        }
        //checking for opcode
        if(strcmp(opcode, "END")!=0)
        {
            //check in optab for instructions
            fseek(optab, SEEK_SET, 0);
            opfound = false;
            while(fscanf(optab,"%s\t%s", code, mnemonic)==2)
            {
                if (strcmp(code, opcode)==0)
                {
                    locctr +=3;
                    opfound = true;
                    printf("Opcode found.");
                    break;
                }
            }
            if (opfound==false)
            {
                if (strcmp(opcode, "WORD")==0)
                {
                    locctr +=3;
                    opfound = true;
                }
                else if (strcmp(opcode, "BYTE")==0)
                {
                    locctr +=1;
                    opfound = true;
                }
                else if (strcmp(opcode, "RESB")==0)
                {
                    locctr +=atoi(operand);
                    opfound = true;
                }
                else if (strcmp(opcode, "RESW")==0)
                {
                    locctr +=3*atoi(operand);
                    opfound = true;
                }
                else
                {
                    printf("Invalid OP code found.");
                    opfound = false;
                    exit(1);
                }
            }
        }
        fprintf(inter,"%s\t%s\t%s\n",label, opcode, operand);
        fscanf(input,"%s\t%s\t%s",label, opcode, operand);
    }
    fprintf(inter,"--\t%s\t%s\n",opcode, operand);
    fclose(input);
    fclose(inter);
    fclose(symsearch);
    fclose(symtab);
    fclose(optab);
    printf("Completed the program.\n");
}

