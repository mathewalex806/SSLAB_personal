#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

# define MAX_SIZE 100

void main()
{
    printf("Enter the number of frames in the main memory: ");
    int frames;
    scanf("%d", &frames);
    int main_memory[frames];
    for (int i = 0; i < frames; i++)
    {
        main_memory[i] = -1;
    }
    printf("Enter the reference string: ");
    int reference_string[MAX_SIZE];
    int reference_string_size;
    scanf("%d", &reference_string_size);
    for (int i = 0; i < reference_string_size; i++)
    {
        scanf("%d", &reference_string[i]);
    }
    int page_faults = 0;
    int page_hits = 0;
    int rear = -1;

    // FIFO Page Replacement Algorithm

    for (int i=0 ; i< reference_string_size; i++)
    {
        bool flag = false;
        for (int j=0; j<frames; j++)
        {
            if (main_memory[j] == reference_string[i])
            {
                flag = true;
                page_hits++;
                break;
            }

        }
        if (!flag)      //Page fault occured
        {
            page_faults++;
            rear = (rear+1)%frames;
            main_memory[rear] = reference_string[i];
            printf("Page fault occured at %d\n", reference_string[i]);
        }

    }
}