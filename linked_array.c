#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

# define MAX_SIZE 100
int disk[MAX_SIZE];
int block_link[MAX_SIZE];


void main()
{
    bool loop = true;
    printf("Enter the number of blocks in the disk :");
    int no_block;
    scanf("%d",&no_block);
    
    for (int i=0; i< no_block; i++)
    {
        disk[i] = 0;
        block_link[i] = -1;
    }
    while(loop)
    {
        printf("\nMenu\n1.Allocate a Block\n2.Print all blocks\n3.Exit\nEnter your choice :");
        int choice;
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                //Allocate a block
                printf("Enter the size of the file :");
                int size;
                scanf("%d",&size);
                printf("Enter the blocks you want to allocate :");
                int blocks[size];
                for (int i=0; i<size; i++)
                {
                    scanf("%d",&blocks[i]);
                }
                bool flag = true;
                for (int i=0; i<size; i++)
                {
                    if (disk[blocks[i]]!=0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    for (int i=0; i<size; i++)
                    {
                        disk[blocks[i]] = 1;
                        if (i==size-1)
                        {
                            block_link[blocks[i]] = -1;
                        }
                        else
                        {
                            block_link[blocks[i]] = blocks[i+1];
                        }
                    }
                    printf("File allocated successfully\n");
                }
                else
                {
                    printf("Failed to allocate file\n");
        }
    }
}
}
