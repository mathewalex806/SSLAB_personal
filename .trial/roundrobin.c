#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct process {
    int pid;
    int bbtime;
    int completion;
};

void main()
{
    int count;
    printf("Enter the number of processes\t:");
    scanf("%d",&count);
    struct process p1[count];
    int totaltime = 0;

    printf("Enter the Pid, burst time  of the processes\t:");
    for (int i=0; i< count; i++)
    {
        scanf("%d%d",&p1[i].pid,&p1[i].bbtime);
        p1[i].completion = 0;
        totaltime += p1[i].bbtime;

    }
    printf("\n\npid\tbbtime\tcompletion\n");
    for (int i=0; i< count; i++)
    {
        printf("%d\t%d\t%d\t\n",p1[i].pid,p1[i].bbtime,p1[i].completion);
    }

    printf("Enter the time quantum\t:");
    int time_slice=0;
    scanf("%d",&time_slice);
    
    int total_count = 0;
    int curtime =0;

    while (total_count<count)
    {
        for (int i=0; i<count; i++)
        {
            if (p1[i].bbtime!=0)
            {
                if (p1[i].bbtime < time_slice)
                {
                    curtime+= p1[i].bbtime;
                    p1[i].bbtime = 0;
                    p1[i].completion = curtime;
                    total_count++;
                }
                else
                {
                    curtime+=time_slice;
                    p1[i].bbtime -= time_slice;
                }
            }
        }
    }

    printf("pid\tbbtime\tcompletion\n");
    for (int i=0; i< count; i++)
    {
        printf("%d\t%d\t%d\t\n",p1[i].pid,p1[i].bbtime,p1[i].completion);
    }


}