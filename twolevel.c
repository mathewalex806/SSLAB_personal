#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100

struct File{
    char name[MAX_SIZE];
};

struct Directory{
    char name[MAX_SIZE];
    int file_count;
    struct File files[MAX_SIZE];
};


struct Directory root[MAX_SIZE];


void main()
{
    //Adding files and listing all the files in the directory.
    int size;
    printf("Enter the size of each directory\t:");
    scanf("%d",&size);
    int cursize =0;
    bool loop = true;
    while (loop)
    {
        int choice =0;
        printf("\nMenu\n1.Add file to a directory.\n2.List all the files\nEnter your choice(1-2):\t");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("Enter the ")

            break;
        
        case 2:
            break;
        
        default:
            break;
        }

    }

}