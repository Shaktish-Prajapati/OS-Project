#include<stdio.h>
#include<stdlib.h>
typedef struct 
{
    int pid,arrTym,busTym,tb,flag,stus;
}process;
process p1[100],p2[100],p3[100];
int extraV1,extraV2,extraV3,prior;
int tymQun1=8,tymQun2=16;
int pCount=0;   //counter for all the processes
void red () {
  printf("\033[1;31m");
}
void yellow (){
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}
void Load(process arr[],int a,int b,int c,int pos)
{
    arr[pos].pid=a;
    arr[pos].arrTym=b;
    arr[pos].busTym=c;
    arr[pos].tb=c;
}
void traverse(process arr[],int n) // to traverse
{
    for(int i=0;i<n;i++)
    {
        printf("pid is:%d",arr[i].pid);
    }
}
void roundRobin(process p[],int tQ,int Ttq,int k)
{
    int i=0,fl=0;
    //traversal(p1,k);
    
    int taTym,wait;
    while(1){
        if(i==k){i=0;}
        if(Ttq==0||fl==k)
          break; //Aging apply
               
        if(p[i].arrTym<=pCount && p[i].stus!=1 && p[i].flag!=1)
        {
            if(tQ<=Ttq){}
            else{tQ=Ttq;}
            if(p[i].tb<=tQ)
            {
                printf("\n\tEnter first\t");
                printf("%d--Total-count value\n",pCount);
                pCount+=p[i].tb;
                taTym=pCount-p[i].arrTym;
                wait=taTym-p[i].busTym;
                p[i].stus=1;
                p[i].flag=1;
                Ttq-=p[i].tb;
                fl++;
                //printf("process with P-id:%d completed\t Waiting time is:%d\tTurn-Around Time is %d\n",p[i].pid,wait,taTym);
                red();
                printf("P-id\t Waiting time\tTurn-Around Time\n"/*,p[i].pid,wait,taTym*/);
                printf("%d\t\t%d\t%d\n",p[i].pid,wait,taTym);
                yellow();
                i++;
                continue;
            }
            if(p[i].tb>tQ)
            {
                p[i].tb-=tQ;
                pCount+=tQ;
                p[i].flag=0;
                Ttq-=tQ;
                i++;
                continue;
            }
        }
        else
        {
            pCount++;
            Ttq--;
            
        }
        i++;
    }
    for(int i=0;i<k;i++)
    {
        p[i].flag=0;
    }
}

void firstCome(process p[],int k)
{
    int wait,Tat;
    for(int i=0;i<k;i++)
    {
        if(p[i].arrTym<=pCount && p[i].stus!=1 && p[i].flag!=1)
        {
            pCount+=p[i].tb;
            Tat=pCount-p[i].arrTym;
            wait=Tat-p[i].busTym;
            p[i].flag=1;
            p[i].stus=1;
            //printf("Process with P-id:\t%d completed\t Waiting Time is:%d\tTurn-around Time is %d\n",p[i].pid,wait,Tat);
            printf("\nP-id\t Waiting time\tTurn-Around Time\n"/*,p[i].pid,wait,taTym*/);
            printf("%d\t\t%d\t%d\n",p[i].pid,wait,Tat);
        }   
        else{
            continue;
        }
    }
}

int main()
{
    int c1=0,c2=0,c3=0;
    int n,j,full=0;
    printf("Enter total number of processes\t:");
    scanf("%d",&n);
    red();
    printf("Reminder--> Do not Exeed Priority more than 3\t");
    j=n;
    while(n!=0)
    {
        yellow();
        printf("\nEnter P-id of process\t\t:");
        scanf("%d",&extraV1);
        printf("Enter Arrival time\t\t:");
        scanf("%d",&extraV2);
        printf("Enter Burst time time\t\t:");
        scanf("%d",&extraV3);
        
        printf("Enter Priority of process\t:");
        scanf("%d",&prior);
        /*Adding elements in array acc 2 prio...*/
        if(prior==1){Load(p1,extraV1,extraV2,extraV3,c1);c1++;}
        else if(prior==2){Load(p2,extraV1,extraV2,extraV3,c2);c2++;}
        else if(prior==3){Load(p3,extraV1,extraV2,extraV3,c3);c3++;}
        else{printf("Wrong priority---Processes has been Stop...\n");exit(-1);}
        n--;
    }
   
    //Aging Implemented
    while(pCount<1000)
    {
    roundRobin(p1,4,8,c1);
    roundRobin(p2,4,16,c2);
    firstCome(p3,c3);
    }

    return 0;
}

