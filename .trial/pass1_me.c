#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char opcode[10], operand[10], mnemonic[10], label[10], code[10];
    FILE *f1, *f2, *f3, *f4;
    int locctr = 0, start = 0, length = 0, label_count = 0;
    char labels[100][10];
    int flag = 0;

    // Open files
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("intertab.txt", "w");

    if (!f1 || !f2 || !f3 || !f4) {
        printf("Error opening files.\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (f3) fclose(f3);
        if (f4) fclose(f4);
        return 1;
    }

    // Read first line to get starting address
    fscanf(f1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(f4, "%s %s %s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    // Main processing loop
    while (strcmp(opcode, "END") != 0) {
        fprintf(f4, "%d ", locctr);
        if (strcmp(label, "**") != 0) {
            // Label exists for the current line
            int is_duplicate = 0;
            for (int i = 0; i < label_count; i++) {
                if (strcmp(labels[i], label) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }
            if (is_duplicate) {
                printf("Duplicate label found at: %d\n", locctr);
                flag = 1;
            } else {
                strcpy(labels[label_count++], label);
                fprintf(f3, "%s %d\n", label, locctr);
            }
        }

        // Searching in the optab
        fseek(f2, 0, SEEK_SET);
        int opcode_found = 0;
        while (fscanf(f2, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(code, opcode) == 0) {
                locctr += 3;
                opcode_found = 1;
                break;  // Break after finding the opcode
            }
        }

        if (!opcode_found) {
            // Check for assembler directives
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "BYTE") == 0) {
                locctr += 1;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else {
                printf("Invalid OP code: %s at location %d\n", opcode, locctr);
                flag = 1;
            }
        }

        fprintf(f4, "%s %s %s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand);
    }

    fprintf(f4, "%d %s\n", locctr, "END");
    length = locctr - start;

    if (flag != 1) {
        printf("Length: %d\n", length);  // Print program length
    } else {
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

    return 0;
}
