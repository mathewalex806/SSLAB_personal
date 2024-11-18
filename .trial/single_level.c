#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_LENGTH 1000

struct File {
    int index;
};

struct Directory {
    struct File files[MAX_LENGTH];
    int size;
};

struct Directory dir;

int main()
{
    int size; 
    printf("Enter the size of directory\t:");
    scanf("%d", &size);
    dir.size = size;
    bool loop = true;
    int cursize = 0;

    while(loop){
        int choice;
        printf("\n Menu \n 1. Add a file\n2. Delete a file\n3. List all the files\nEnter your choice(1-3):\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (dir.size == cursize){
                printf("Reached maximum directory size.\n");
                break;
            }
            else{
                int index_file;
                printf("Enter the unique index name for the file: ");
                scanf("%d", &index_file);
                dir.files[cursize].index = index_file;
                cursize++;
                printf("Allocated file %d\n", index_file);
            }
            break;
        
        case 2: {
            int index_file;
            printf("Enter the index of the file to delete\t:");
            scanf("%d", &index_file);
            bool found = false;

            for (int i = 0; i < cursize; i++)
            {
                if (dir.files[i].index == index_file)
                {
                    found = true;
                    for (int j = i; j < cursize - 1; j++)
                    {
                        dir.files[j].index = dir.files[j+1].index;
                    }
                    cursize--;
                    printf("Deallocated the file\n");
                    break;
                }
            }
            if (!found){
                printf("\nFile index not found\n");
            }
            break;
        }
        
        case 3:
            if (cursize == 0) {
                printf("No files available\n");
            } else {
                for (int i = 0; i < cursize; i++)
                {
                    printf("File %d\t", dir.files[i].index);
                }
                printf("\n");
            }
            break;
        
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}
