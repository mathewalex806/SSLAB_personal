#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main()
{
    char opcode[10], operand[10], mnemonic[10], label[10], code[10];
    FILE *f1, *f2, *f3, *f4;
    int locctr=0, start=0, length=0, label_count=0;
    char labels[100][10];
    int flag=0;


    f1 = fopen("input.txt","r");
    f2 = fopen("optab.txt","r");
    f3 = fopen("symtab.txt","w");
    f4 = fopen("intertab.txt","w");

    if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL)
    {
        printf("Error opening files.\n");
        flag=1;
        fclose(f1);
        fclose(f2);
        fclose(f3);
        fclose(f4);
        return 1;
    }
    //Reading the first line of the input file to get the starting address

    fscanf(f1,"%s\t%s\t%s",label,opcode, operand);
    if (strcmp(opcode,"START")==0)
    {
        start = atoi(operand);
        locctr = start;
        //Writing the first line to the intermediate file
        fprintf(f4,"%s\t%s\t%s",label,opcode,operand);
        fscanf(f1,"%s\t%s\t%s",label,opcode, operand);
    }
    else
    {
        locctr = 0;
    }
    while (strcmp(opcode,"END")!=0)
    {
        fprintf(f4,"%d\t",locctr);
        if (strcmp(label,"**")!=0)
        {
            //label exists for the current line 
            int is_duplicate = 0;
            for (int i=0 ; i<label_count; i++)
            {
                if (strcmp(labels[i],label)==0)
                {
                    is_duplicate = 1;
                    break;
                }
            }
            if (is_duplicate)
            {
                printf("Duplicate label found at :%d",locctr);
                flag = 1;
            }
            else
            {
                strcpy(labels[label_count++],label);
                fprintf(f3,"%s\t%s",label,locctr);
            }
        }

        //Searching in the optab part
        fseek(f2,0,SEEK_SET);
        int opcode_found =0;
        while(fscanf(f2,"%s\t%s",code, mnemonic)!=EOF)
        {
            if (strcmp(code, opcode)==0)
            {
                locctr+=3;
                opcode_found = 1;

            }
        }
        if (opcode_found==0)
        {
            //Check for assembler directives
            if (strcmp(opcode,"WORD")==0)
            {
                locctr+=3;
            }
            if (strcmp(opcode,"BYTE")==0)
            {
                locctr+=1;
            }
            if (strcmp(opcode,"RESW")==0)
            {
                locctr+=3*atoi(operand);
            }
            if (strcmp(opcode,"RESB")==0)
            {
                locctr+=atoi(operand);
            }
            else
            {
                printf("Invalid OP code.\n");
                flag =1;
            }

        }
        fprintf(f4,"%s\t%s\t%s",label,opcode,operand);
        fscanf(f1,"%s\t%s\t%s",label,opcode, operand);
    }
    fprintf(f4, "%d\t%s\t%s\n", locctr, "END", "");
    length = locctr - start;
    if (flag != 1)
    {
        printf("Length: %d\n", length);  // Print program length
    }
    else
    {
        // If an error occurred, clear the symbol and intermediate tables
        printf("Error occurred. Clearing symbol and intermediate tables.\n");
        fclose(f3);
        fclose(f4);
        f3 = fopen("symtab.txt", "w");
        f4 = fopen("intertab.txt", "w");
        fprintf(f3, "");  // Clear symbol table
        fprintf(f4, "");  // Clear intermediate table
    }

    // Close all files
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
}
