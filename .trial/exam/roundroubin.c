#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process
{
    int pid;
    int btime;
    int completion;

    bool completed;
    int remain;
};


void display(struct Process p1[], int n)
{
    printf("Displaying the values\nPID\tBursttime\tCompletion\n");
    for (int i=0 ; i< n; i++)
    {
        printf("%d\t%d\t%d\t\n",p1[i].pid, p1[i].btime,p1[i].completion);
    }
}

void roundrobin(struct Process p1[], int n)
{
    int tq;
    printf("Enter the time quantum for the algorithm\t:");
    scanf("%d",&tq);
    printf("\n%d\n",tq);
    int completed = 0;
    int time =0;
    while (completed!=n)
    {
        for (int i=0 ; i< n; i++)
        {
            if (p1[i].completed == false)
            {
                if (p1[i].remain <= tq)
                {
                    time += p1[i].remain;
                    p1[i].remain = 0;
                    p1[i].completion = time;
                    p1[i].completed = true;
                    completed++;
                }
                else
                {
                    time+=tq;
                    p1[i].remain -=tq;
                }
            }
        }
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
        p1[i].pid = i;
        p1[i].completion = 0;
        p1[i].completed = false;
        p1[i].remain = p1[i].btime;
    }
    display(p1, n);
    roundrobin(p1,n);
}

void main()
{
    int no_process;
    printf("Round robin CPU scheduling algorithm.\nEnter the number of processes\t:");
    scanf("%d",&no_process);

    struct Process p1[no_process];

    intitialize(p1, no_process);
}