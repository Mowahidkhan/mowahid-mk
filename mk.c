#include<stdio.h>
#include<stdlib.h>

struct process{
    char pid;
    char status;
    int at,nut;
    int wt;
    int q;
    int st;
    struct process *next;
 } ;
 struct process * getRunning();
 void addToReady(struct process *);
 void addToWaiting(struct process *);
 void updateStatus(struct process *);
void getUserInput();
void getUserData();
void generateData();
 void showStatus(int t);
 void updateWaitingTime();
void addToNAF(struct process *);
void addToProcesses(struct process *);
void showDataFileFormat();
 struct process * ReadyFront=NULL,*ReadyRear=NULL,*WFront=NULL,*WRear=NULL,*NAF=NULL,*NAR=NULL;
 struct process * processesF=NULL, *processesR=NULL;
int quant,noOfP;
FILE *fptr;

 
 int main(){
     int n=0,t=0,qt=0,ch;struct process * temp,*running;
	printf("\nChoices Available:\n");
	printf("\n1. User Input.\n");
	printf("2. Auto Generated.\n");
	showDataFileFormat();
	printf("\nEnter Choice:");
	scanf("%d",&ch);
     if(ch==1){
	/**/
	getUserData();
	//getUserInput();
	}
	else if(ch==2){
	generateData();
	}
	else
	{
	printf("\n Wrong choice entered. Try Again.\n");
	exit(0);
	}
	fptr=fopen("Output.txt","w");
	printf("\n No of Processes %d, Quant time %d\n",noOfP,quant);
	fprintf(fptr,"\n No of Processes %d, Quant time %d\n",noOfP,quant);
	fprintf(fptr,"\nT");
     
     printf("\nT");
     for(temp=processesF;temp!=NULL;temp=temp->next){
         printf("\t %c",temp->pid);
	fprintf(fptr,"\t %c",temp->pid);
        }
     printf("\n");fprintf(fptr,"\n");
	qt=quant;
	n=noOfP;
     
     for(t=0;n>=0;t++)
     {
         for(temp=NAF;temp!=NULL;temp=temp->next) {
            if(temp->status=='N'&&temp->at==t){
                 //printf("%c",temp->pid);
                addToReady(temp);
                 //NAF=NAF->next;
            }
             }
         if(ReadyRear!=NULL)
             ReadyRear->next=NULL;
        if(qt==quant)
         {
             running=getRunning(t);
          }
         if(n==0)
         {
             showStatus(t);
             break;
         }
	 if(running!=NULL){
         running->status='R';
         updateStatus(running);
         showStatus(t);
         updateWaitingTime();
        running->nut-=1;
         running->q+=1;
        // printf("Executing %c",running->pid);
         if(running->nut==0){
             running->status='F';
             updateStatus(running);
             n--;
             qt=quant;
         }else{
             qt--;
             if(qt==0){
                 running->status='W';
                 //printf("status changes to W %c\n",running->pid);
                 updateStatus(running);
                // printf("Added to waiting %c\n",running->pid);
                 addToWaiting(running);
                 qt=quant;
             }
         }}else{showStatus(t);}
         
      
     }
     for(temp=processesF;temp!=NULL;temp=temp->next){
         printf("\n Process id: %c , Arrival time:%d ,Start Time:%d,Waiting Time:%d, Burst Time:%d,Turnaround time:%d, Penalty ratio:%2f",
temp->pid,temp->at,temp->st,temp->wt,temp->nut,(temp->nut+temp->wt),((float)temp->nut/(temp->nut+temp->wt)));
	fprintf(fptr,"\n Process id: %c , Arrival time:%d ,Start Time:%d,Waiting Time:%d, Burst Time:%d,Turnaround time:%d, Penalty ratio:%2f",
temp->pid,temp->at,temp->st,temp->wt,temp->nut,(temp->nut+temp->wt),((float)temp->nut/(temp->nut+temp->wt)));
     }
	printf("\n");fprintf(fptr,"\n");
	fclose(fptr);
	printf("\nSee the details of last run in Output.txt file.\n");
             
     return 0;
 }
 
 
 
 void addToReady(struct process * temp)
 {
     temp->status='W';
         temp->q=0;
         temp->wt=0;
         updateStatus(temp);
         struct process *temp1;
         //printf("%c added to ready",temp->pid);
         temp1= (struct process *)malloc(sizeof( struct process));
      temp1->pid=temp->pid;
      temp1->at=temp->at;
      temp1->nut=temp->nut;
      temp1->status=temp->status;
      temp1->q=temp->q;
      temp1->wt=temp->wt;
         //printf("%c added to ready",temp->pid);
     if(ReadyFront==NULL)
     {        
         ReadyFront=temp1;
         ReadyRear=temp1;
         ReadyRear->next=NULL;         
     }else{
         ReadyRear->next=temp1;
         ReadyRear=temp1;
        ReadyRear->next = NULL;
     }
 }
 void updateStatus(struct process * temp)
 {
     struct process * temp1;
     for(temp1=processesF;temp1!=NULL;temp1=temp1->next)
     { if(temp1->pid==temp->pid){
         temp1->q=temp->q;
     temp1->status=temp->status;
     temp1->wt=temp->wt;
     temp1->st=temp->st;
     }}
 }
 
 struct process * getRunning(int t)
 {
     struct process *running;
     if(ReadyFront!=NULL){
         running=ReadyFront;
         running->st=t;
         updateStatus(running);
         ReadyFront=ReadyFront->next;
     }else if(WFront!=NULL)
     {
         running=WFront;
         WFront=WFront->next;
     }else 
         running=NULL;
     
       return running;
 }
 void addToWaiting(struct process * temp)
 {
     struct process *temp1;
         //printf("%c added to ready\n",temp->pid);
      temp1= (struct process *)malloc(sizeof( struct process));
      temp1->pid=temp->pid;
      temp1->at=temp->at;
      temp1->nut=temp->nut;
      temp1->status=temp->status;
      temp1->q=temp->q;
      temp1->wt=temp->wt;
      temp1->st=temp->st;
   if(WFront==NULL)
     {        
         WFront=temp1;
         WRear=temp1;
         WRear->next=NULL;         
     }else{
       WRear->next=temp1;
       temp1->next=NULL;
       WRear=temp1;
     }
       
    }
 void showStatus(int t)
 {
     
     printf("%d",t);fprintf(fptr,"%d",t);
     struct process * temp;
     for(temp=processesF;temp!=NULL;temp=temp->next){
         if(temp->status=='F')
             {printf("\tF");fprintf(fptr,"\tF");}
         else if(temp->status=='N')
             {printf("\t-");fprintf(fptr,"\t-");}
         else
             {printf("\t%c(q%d)",temp->status,temp->q);fprintf(fptr,"\t%c(q%d)",temp->status,temp->q);}
        }
     printf("\n");fprintf(fptr,"\n");
 }
 
 void updateWaitingTime(){
     struct process * temp;
     for(temp=ReadyFront;temp!=NULL;temp=temp->next){
         if(temp->status=='W'){
             temp->wt+=1;
         }
     }
     for(temp=WFront;temp!=NULL;temp=temp->next){
         if(temp->status=='W'){
             temp->wt+=1;
         }
 }
 }
void getUserInput()
{
int i=0,a,nt;struct process * temp;
printf("Enter no of process:");
	scanf("%d",&noOfP);
	//initialize();

for(i=0;i<noOfP;i++)
{
printf("For process %c\n",(i+65));
printf("Enter arrival time:");scanf("%d",&a);
printf("Enter cpu burst time:");scanf("%d",&nt);
temp=(struct process *)malloc(sizeof(struct process));
temp->pid=(char)i+65;
temp->at=a;
     temp->nut=nt;
     temp->status='N';
     temp->q=-1;
     temp->next=NULL;
	addToNAF(temp);
	addToProcesses(temp);
}
printf("Enter quant time:");scanf("%d",&quant);
//initialize();
}
void generateData(int n)
{
int i=0,a,nt;struct process * temp;
time_t tt;
srand((unsigned) time(&tt));

	noOfP=1+rand()%4;

	quant=1+rand()%2;
for(i=0;i<noOfP;i++)
{
a=0+rand()%4;
nt=1+rand()%4;
temp=(struct process *)malloc(sizeof(struct process));
temp->pid=(char)i+65;
temp->at=a;
     temp->nut=nt;
     temp->status='N';
     temp->q=-1;
     temp->next=NULL;
	addToNAF(temp);
	addToProcesses(temp);
}
//initialize();
}


void addToNAF(struct process * temp)
{
struct process *temp1;
         //printf("%c added to ready\n",temp->pid);
      temp1= (struct process *)malloc(sizeof( struct process));
      temp1->pid=temp->pid;
      temp1->at=temp->at;
      temp1->nut=temp->nut;
      temp1->status=temp->status;
      temp1->q=temp->q;
      temp1->wt=temp->wt;
      temp1->st=temp->st;
   if(NAF==NULL)
     {        
         NAF=temp1;
         NAR=temp1;
         NAR->next=NULL;         
     }else{
       NAR->next=temp1;
       temp1->next=NULL;
       NAR=temp1;
     }
}
void addToProcesses(struct process * temp)
{
struct process *temp1;
         //printf("%c added to ready\n",temp->pid);
      temp1= (struct process *)malloc(sizeof( struct process));
      temp1->pid=temp->pid;
      temp1->at=temp->at;
      temp1->nut=temp->nut;
      temp1->status=temp->status;
      temp1->q=temp->q;
      temp1->wt=temp->wt;
      temp1->st=temp->st;
   if(processesF==NULL)
     {        
         processesF=temp1;
         processesR=temp1;
         processesR->next=NULL;         
     }else{
       processesR->next=temp1;
       temp1->next=NULL;
       processesR=temp1;
     }
}
 

void getUserData(){
char line[200];int limit=200;
	int N,a,nt,q,i=0;char pid;FILE *f;struct process * temp;

    /* now open it and read it */
    f = fopen("data.txt", "r");
	if(f==NULL)
	{
	printf("Error in reading file. Make sure it exists and contents are in proper format.\n\n");
	exit(0);
	}

    fgets(line,limit,f);sscanf(line,"%d",&noOfP);
	for(i=0;i<noOfP;i++)
	{
	fgets(line,limit,f);
	sscanf(line,"%d%d",&a,&nt);
	//printf("process %c at %d nut %d\n",pid,a,nt);
	temp=(struct process *)malloc(sizeof(struct process));
	temp->pid=(char)i+65;
	temp->at=a;
     	temp->nut=nt;
     	temp->status='N';
     	temp->q=-1;
     	temp->next=NULL;
	addToNAF(temp);
	addToProcesses(temp);
	}
	fgets(line,limit,f);sscanf(line, "%d", &quant);//printf("\nQuant %d",q);
        
    fclose(f);

}



void showDataFileFormat(){
printf("\n Note: \nIf option 1 is selected, please keep the data.txt file ready.\n");
printf("The content of data file should be as follows:\n");
printf("First line should be an integer representing no of process N.\n");
printf("Followed by N lines containinig 2 integers, ie ,arrival time and burst time of each process.\n");
printf("The Last line shloud be an integer representing quanta.\n");
printf("A typical data.txt file should be like this:\n");
printf("3\n");//for no of process, N=3
printf("0 2\n");//arrival time and burst time of 1st process
printf("0 3\n");//arrival time and burst time of 2nd process
printf("3 2\n");//arrival time and burst time of 3rd process
printf("1\n");//for quanta, quanta=1
}

