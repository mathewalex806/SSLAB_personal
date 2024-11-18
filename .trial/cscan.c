#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void main()
{
  int n,m;
    printf("Enter no. of Processes:");
    scanf("%d",&n);
    printf("Enter no. of resources:");
    scanf("%d",&m);
    int Allocation[n][m],Max[n][m],Available[m],Need[n][m],Work[m],Finish[n],safesequence[n],ind=0,completed=0;
    printf("Enter Allocation matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&Allocation[i][j]);
        }
    }
    printf("Enter Maximum matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&Max[i][j]);
        }
    }
    printf("Enter Available Resources:");
    for(int i=0;i<m;i++){
        scanf("%d",&Available[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            Need[i][j]=Max[i][j]-Allocation[i][j];
        }
    }
    for(int i=0;i<n;i++){
        Finish[i]=0;
    }
    for(int i=0;i<m;i++){
        Work[i]=Available[i];
    }  
    int flag =1;
    while (completed!=n) 
    {
        for (int i=0 ; i<n; i++)
        {
            if (Finish[i] ==0)
            {
                flag = 1;
                for (int j =0 ; j< m ; j++ )
                {
                    if (Need[i][j] > Work[j])
                    {
                        flag = 0;
                        break;
                    }

                }
                if (flag == 1)
                {
                    printf("completed process %d",i);
                    for(int k=0;k<m;k++)
                    {
                        Work[k]+=Allocation[i][k];
                    }
                    Finish[i]=1;
                    completed++;
                }
            }
           
        }
    }
}