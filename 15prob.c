//CPU schedules N processes which arrive at different time intervals and each process is allocated the CPU...
#include<stdio.h>
#include<fcntl.h>
typedef struct 
{
    int pId, arrTym, bursTym,tb,pR,flag,stat;
}process;
process p1[100];
int sumWt,sumTT;
int fl=0;
int c1=0;
int frst=1;

int tCnt=0;
int previndx=0;
int max(process p[],int k)
{
    int indx=0;
    int max=-9999;
    for(int i=0;i<k;i++)
    {
        if(p[i].arrTym<=tCnt && p[i].pR>max && p[i].flag!=1 && p[i].stat!=1)
        {
            indx=i;
            max=p[i].pR;
            p[i].stat=0;
        }
        
    }
    for(int i=0;i<k;i++)
    {
        if(p[i].stat!=1 && p[i].flag!=1 && i!=indx)
        {
            if(i==indx){p[i].stat=0;continue;}
            p[i].stat=-2;
        }
    }
    return indx;
}
void red () {
  printf("\033[1;31m");
}
void yellow (){
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}
void travers(process arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("pId is:%d",arr[i].pId);
    }
}

void Load(process arr[],int a,int b,int c,int d,int pos)
{
    arr[pos].pId=a;
    arr[pos].arrTym=b;
    arr[pos].bursTym=c;
    arr[pos].tb=c;
    arr[pos].pR=d;
}

void firstCome(process p[],int k)
{
    int Tat=0,wait=0;
    for(int i=0;i<k;i++)
    {
        if(p[i].stat==-2 && p[i].flag!=1 && p[i].arrTym<=tCnt)
        {
            tCnt+=p[i].tb;
            p[i].tb=0;
            Tat=tCnt-p[i].arrTym;
            wait=Tat-p[i].bursTym;
            sumWt+=wait;
            sumTT+=Tat;
            p[i].flag=1;
            p[i].stat=1;
            printf("\nprocess with pId[%d] COMPLETED\tWaitTime is[%d]\tTurn-AroundTime is [%d]\n",p[i].pId,wait,Tat);
            fl++;
        }
    }
    for(int i=0;i<k;i++)
    {
        if(p[i].stat!=1)
        {
        p[i].flag=0;
        p[i].stat=0;
        }
    }
}


void roundRobin(process p[],int tymQ,int TtltymQ,int k)
{
    int i=0,indx=0;
  
    int TurnAround,wait;
    while(1){
       
        if(i==k){i=0;}
        if(fl==k)break; //Aging Apply
           
        indx=max(p,k);
        if(frst==1){    tCnt=p[indx].arrTym;frst++;}
        if(indx!=previndx){
            tymQ=4;
        }
        
        previndx=indx;
        if(TtltymQ>0)//Aging Apply
        {
            if(TtltymQ<tymQ){tymQ=TtltymQ;}
                tCnt++;
                
                TtltymQ--;
                p[indx].tb--;
                tymQ--;
                if(p[indx].tb==0)
                {
                 TurnAround=tCnt-p[indx].arrTym;
                 wait=TurnAround-p[indx].bursTym;
                 sumWt+=wait;
                 sumTT+=TurnAround;
                 p[indx].flag=1;
                 p[indx].stat=1;
                 fl++;
                 red();
                 //printf("\nprocess with pId[%d] Complete\tWaitTime is[%d]\tTurn-AroundTime is [%d]\n"/*,p[indx].pId,wait,TurnAround*/);
                 printf("\nprocess P-Id\tWaitTime is\tTurnAround Time\n"/*,p[indx].pId,wait,TurnAround*/);
                 printf("\n%d\t\t%d\t\t%d\n",p[indx].pId,wait,TurnAround);
                 continue;
                }
            if(tymQ==0)
            {
                p[indx].flag=1;
            }
            
        }
        else{
          yellow();
            printf("Time Quantum Expire");
            red();
            firstCome(p,c1);
            TtltymQ=16;
        }

}
}
int main()
{
    int extraV1=0,extraV2=0,extraV3=0,pR=0;
    int n,j,full=0;
    red();
    printf("Enter total number of processes\t:");
    scanf("%d",&n);
    j=n;
    while(n!=0)
    {
        yellow();
        printf("\nEnter P-Id of process\t\t:");
        scanf("%d",&extraV1);
        printf("Enter Arrival time\t\t:");
        scanf("%d",&extraV2);
        printf("Enter Burst time\t\t:");
        scanf("%d",&extraV3);
        printf("Enter Priority of process\t:");
        scanf("%d",&pR);
        Load(p1,extraV1,extraV2,extraV3,pR,c1);c1++;
        n--;
    }
    
    roundRobin(p1,4,16,c1);
    yellow();
    printf("\n\nAverage Waiting Time: %d \t Average Turn Around Time:%d\n\n",sumWt,sumTT);
    return 0;
}
