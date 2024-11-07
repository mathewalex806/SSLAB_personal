#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process {
    int pid;
    int bbtime;
    int completion;
    int priority;
};

void main()
{
    int count;
    printf("Enter the number of processes\t:");
    scanf("%d",&count);
    struct process p1[count];

    printf("Enter the Pid, burst time and the priority of the processes\t:");
    for (int i=0; i< count; i++)
    {
        scanf("%d%d%d",&p1[i].pid,&p1[i].bbtime,&p1[i].priority);
        p1[i].completion = 0;
    }
    printf("\n\npid\tbbtime\tpriority\tcompletion\n");
    for (int i=0; i< count; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p1[i].pid,p1[i].bbtime,p1[i].priority,p1[i].completion);
    }

    for (int i=0; i< count-1; i++ )
    {
        for (int j=0; j< count-1-i; j++)
        {
            if (p1[j+1].priority>p1[j].priority )
            {
                struct process temp = p1[j+1];
                p1[j+1] = p1[j];
                p1[j] = temp;
            }
        }
    }
    printf("\n");
    for (int i=0; i< count; i++)
    {
        printf("%d\t%d\t%d\n",p1[i].pid,p1[i].bbtime,p1[i].priority);
    }

    int time=0;

    for(int i=0; i<count;i++)
    {
        time+=p1[i].bbtime;
        p1[i].completion = time;
    }
    printf("pid\tbbtime\tpriority\tcompletion\n");
    for (int i=0; i< count; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p1[i].pid,p1[i].bbtime,p1[i].priority,p1[i].completion);
    }
}