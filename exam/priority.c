#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process 
{
    int pid;
    int priority;
    int btime;
    int completion;
};


void display(struct Process p1[], int n)
{
    printf("Displaying the values\nPID\tBursttime\tCompletion\n");
    for (int i=0 ; i< n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p1[i].pid, p1[i].btime,p1[i].completion, p1[i].priority);
    }
}

void priority_schedule(struct Process p1[], int n)
{
    //Sorting the processes

    for(int i=0 ; i<n-1; i++)
    {
        for (int j=0; j<n-1-i; j++)
        {
            if (p1[j].priority<p1[j+1].priority)
            {
                struct Process temp  = p1[j];
                p1[j] = p1[j+1];
                p1[j+1] = temp;
            }
        }
    }

    //Calculating times
    int time = 0;
    for (int i=0; i<n; i++)
    {
        time+=p1[i].btime;
        p1[i].completion = time;
    }

    display(p1,n);
}


void intitialize(struct Process p1[], int n)
{
    printf("Enter the values into the process");

    for (int i=0; i< n; i++)
    {
        printf("\nEnter the values for process %d\n",i);
        printf("Enter the bursttime\t:");
        scanf("%d",&p1[i].btime);
        printf("Enter the priority of the process\t:");
        scanf("%d",&p1[i].priority);
        p1[i].pid = i;
        p1[i].completion = 0;
    }
    display(p1, n);
    priority_schedule(p1,n);
}


void main()
{
    int no_process;
    printf("Priority CPU scheduling algorithm.\nEnter the number of processes\t:");
    scanf("%d",&no_process);
    struct Process p1[no_process];
    intitialize(p1, no_process);

}