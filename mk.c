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
 
