#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

# define MAX_SIZE 100
int disk[MAX_SIZE];
int no_block;
struct Block{
    int index;
    struct Block* next;
};

struct File{
    char name[MAX_SIZE];
    int size;
    struct Block* head;
};

struct File files[MAX_SIZE];

void allocateFile()
{   
    printf("\nEnter the name of the file :");
    char name[MAX_SIZE];
    scanf("%s",name);
    printf("Enter the size of the file :");
    int size ;
    scanf("%d",&size);
    int count =0;
    for (int i=0; i< no_block; i++)
    {
        if (disk[i] == 0)
            count++;
        
    }
    if (count<size)
    {
        printf("Failed to allocated File.");
        return;
    }
    else
    {
       
    }
}

void main()
{
    bool loop = true;
    printf("Enter the number of blocks in the disk :");
    scanf("%d",&no_block);
    
    for (int i=0; i< no_block; i++)
    {
        disk[i] = 0;
    }
    while(loop)
    {
        printf("\nMenu\n1.Allocate a Block\n2.Print all blocks");
        int choice;
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                allocateFile();
                break;
            case 2:
                break;
            default:
                loop = false;
                break;
        }
    }
}