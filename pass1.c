#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_LABELS 100 
 
int main() 
{               
    char opcode[10], operand[10], mnemonic[10], label[10], code[10];         
    FILE *f1, *f2, *f3, *f4;
    int locctr=0, start=0, length=0, label_count=0;
    char labels[MAX_LABELS][10];
    int flag=0;
    
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("intertab.txt", "w");
 
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
 
    fscanf(f1, "%s %s %s", label, opcode, operand);
    
    if (strcmp(opcode, "START") == 0) 
    {
        start = atoi(operand);
        locctr = start;
        fprintf(f4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand); 
    } 
    else 
    {
        locctr = 0;
    }
 
    while (strcmp(opcode, "END") != 0) 
    {
        fprintf(f4, "%d\t", locctr);
        
        if (strcmp(label, "**") != 0) 
        {
            int is_duplicate = 0;
            for (int i = 0; i < label_count; i++) 
            {
                if (strcmp(labels[i], label) == 0) 
                {
                    is_duplicate = 1;
                    break;
                }
            }
            
            if (is_duplicate) 
            {
                printf("Warning: Duplicate label found: %s at address: %d\n", label,locctr);
                flag=1;
                
            } 
            else 
            {
                strcpy(labels[label_count++], label);
                fprintf(f3, "%s\t%d\n", label, locctr);
            }
        }
 
        // Resetting file pointer for opcode
        fseek(f2, 0, SEEK_SET);
        int opcode_found = 0; 
        
        while (fscanf(f2, "%s\t%s", code, mnemonic) != EOF) 
        {
            if (strcmp(opcode, code) == 0) 
            {
                locctr += 3; 
                opcode_found = 1;
                break;
            }
        }
 
        if (!opcode_found) 
        {
            if (strcmp(opcode, "WORD") == 0) 
            {
                locctr += 3; 
            } 
            else if (strcmp(opcode, "BYTE") == 0) 
            {
                locctr += 1; 
            } 
            else if (strcmp(opcode, "RESB") == 0) 
            {
                locctr += atoi(operand); 
            } 
            else if (strcmp(opcode, "RESW") == 0) 
            {
                locctr += 3 * atoi(operand); 
            } 
            else 
            {
                printf("Invalid opcode: %s at address: %d\n", opcode,locctr);
                flag=1; 
            }
        }
 
        fprintf(f4, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand);     
    }
 
    fprintf(f4, "%d\t%s\t%s\n", locctr, "END", "");
    
    length = locctr - start;
    if(flag != 1)
    {
        printf("Length: %d\n", length);
    }
    else
    {
        fclose(f3);
        fclose(f4);
        f3 = fopen("symtab.txt", "w");
        f4 = fopen("intertab.txt", "w");
        fprintf(f3,"");
        fprintf(f4,"");
    }
    
    
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    return 0;
}
