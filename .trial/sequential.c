#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
# define MAX_SIZE 100

struct File {
    char name[100];
    int start_index;
    int length;
};

int disk[MAX_SIZE];

struct File files[MAX_SIZE];

void main()
{
    printf("Initializing the disk\nEnter the size of the disk: ");
    int disk_size;
    scanf("%d", &disk_size);
    for (int i = 0; i < disk_size; i++)
    {
        disk[i] = 0;
    }
    bool flag = true;
    int files_allocated =0;
    while (flag)
    {
        printf("Enter the operation you want to perform\n1. Create a file\n2. Display the files\nEnter your choice :\n");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                //Creating a file
                if (files_allocated == MAX_SIZE)
                {
                    printf("Disk is full\n");
                    break;
                }
                printf("Enter the name of the file:");
                char name[100];
                scanf("%s", name);
                printf("Enter the length of the file:");
                int length;
                scanf("%d", &length);
                bool allocated = false;
                for (int i=0; i<disk_size; i++)
                {
                    if (disk[i]==0)
                    {
                        bool flag1 = true;
                        for (int j=i ; j<i+length; j++)
                        {
                            if (disk[j]!=0)
                            {
                                flag1 = false;
                                break;
                            }
                        }
                        if (flag1)
                        {
                            //Allocating the file
                            for(int j=i; j<i+length; j++)
                            {
                                disk[j] = 1;
                            }
                            int start_index = i;
                            files[i].start_index = start_index;
                            files[i].length = length;
                            for (int j=0; j<MAX_SIZE; j++)
                            {
                                files[i].name[j] = name[j];
                            }
                            printf("File allocated successfully\n");
                            allocated = true;
                            files_allocated++;
                            break;
                        }
                    }
                  
                }
                  if (!allocated)
                    {
                        printf("Sufficent space unavailable.\n");
                    }
                break;
            case 2:
                //Listing all the files
                for (int i=0; i<MAX_SIZE; i++)
                {
                    if (files[i].length!=0)
                    {
                        printf("File name: %s\n", files[i].name);
                        printf("Start index: %d\n", files[i].start_index);
                        printf("Length: %d\n", files[i].length);
                    }
                }
                break;
            default:
                flag = false;
                break;

    }

}
}