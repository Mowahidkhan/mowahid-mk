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

 
