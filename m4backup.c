//This is a backup of the minor4.c that is working before changes made.
/*Author: Jorge Moreno
  Instructor: Professor Mark Thompson
  Date: 2/28/18
  Description: This program implements a simulation for the Shortest
  Remaining Time First (SRTF) scheduling algorithm. */

#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
  char processID[7];
  int arrivalTime;
  int burstTime;
  int waitTime;
  int remain;
  int finish;
  int pastturn;
}process;

int main()
{
  int i; //loop variable
  int j=0;   //loop variable
  FILE *fp;  //The file variable for opening the file
  char fileN[30];  //holds the file name
  char tempprocessID[7];  //the process id for a process in the file
  int temparrivalTime;  //the arrival time for a process in the file
  int tempburstTime;  //the burst time for a process in the file
  int numProcess = 0;  //number of processes in the file
  int cSwitch = 1;
  int burstTotal=0;
  float avgwait=0;
  float avgthrough=0;
  float avgturn;
  int turntime=0;
  int finaltime=0;
  int shortest;
  int turn = 0;
  int waitTotal=0;
  int check=1;

  printf("Please enter the filename to open.\n");
  scanf("%s",fileN);
  
  fp = fopen(fileN,"r+");
  if(fp == NULL)
  {
    printf("File could not open.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("File has been opened and is ready for use.\n");
  }
  while(!feof(fp))
  {
    fscanf(fp,"%s %d %d", tempprocessID, &temparrivalTime, &tempburstTime);
    numProcess++;
  }

  process *pro = malloc(numProcess *sizeof(process));
  fseek(fp,0,SEEK_SET);
  for(i=0;i<numProcess;i++)
{
  fscanf(fp,"%s %d %d", pro[i].processID,&pro[i].arrivalTime,&pro[i].burstTime);
}
  printf("\nPrinting the processes and info to make sure it works.\n");
for(i=0;i<numProcess;i++)
{
  printf("%s %d %d\n", pro[i].processID,pro[i].arrivalTime,pro[i].burstTime);
}
// Finding all the times and values
//printf("\nThe initial remain time for ach process.\n");
for(i=0;i<numProcess;i++)  //maybe can do in the strut
{
 pro[i].remain =0;
}
for(i=0;i<numProcess;i++)
{
 finaltime += pro[i].burstTime;
}
 
  //avgthrough = (float)numProcess/(float)burstTotal;
  //printf("Average Throughput: %.3f\n",avgthrough); 
 
while(check==1)
{
  if(turn >0)
  {
   for(i=0;i<numProcess;i++)  //setting each process remain time to their burst time
   {
    pro[i].pastturn = pro[i].remain;
   }
  }  
  for(i=0;i<numProcess;i++)  //setting each process remain time to their burst time
  {
   if(turn == pro[i].arrivalTime)
   {
    pro[i].remain = pro[i].burstTime;
    cSwitch++;
   }
  }
 for(i=0;i<numProcess;i++)
 {
  if(pro[i].remain !=0)
  {
    turntime++;
  }
 }
 i =0;
 /*while(pro[shortest].remain == 0)
 {
   shortest =i;
   i++;
 }*/
 do
 {
   shortest=i;
   i++;
 }while(pro[shortest].remain == 0);

 for(i=0;i<numProcess;i++)
 {
   if(pro[i].remain < pro[shortest].remain)// && pro[i].remain > 0)
   {
     if(pro[i].remain >0)
     {
     shortest = i;
     }
   } 
 }
 pro[shortest].remain--;
  turn++;
  for(i=0;i<numProcess;i++)
  {
    if(pro[i].remain > 0)
    {
      if(i != shortest)
      {
        pro[i].waitTime++;
        waitTotal++;
      }
    }
  }
  for(i=0;i<numProcess;i++)
  {
    if(pro[i].pastturn == 1) //&& pro[i].remain == 0)
    {
      if(pro[i].remain == 0)
      {
       pro[i].finish = turn;
      }
    }
  }
 /* for(i=0;i<numProcess;i++)
  {
    pro[i].waitTime = ((pro[i].finish - pro[i].arrivalTime) - pro[i].burstTime);
    if(pro[i].waitTime < 0)
    {
      pro[i],waitTime = 0;
    }
  }*/
  for(i=0;i<numProcess;i++)
  {
    if(pro[i].remain != 0)
    {
      check = 1;
      break;
    }
    else
    {
     check = 0;
      break;
    }
  }
  /*if(check ==1)
  {
    break;
  }
  else if(check ==0)
  {
    break;
  }*/
}
avgthrough = (float)numProcess / (float)turn;
avgwait = (float)waitTotal / (float)numProcess;
avgturn = (float)turntime / (float)numProcess;
printf("\nPID   Arrive   Burst   Remain   Finish   Wait\n");
printf("-----------------------------------------------\n");
for(i=0;i<numProcess;i++)
{
  printf("%s      %d      %d      %d        %d     %d\n",pro[i].processID,pro[i].arrivalTime,pro[i].burstTime,pro[i].remain,pro[i].finish,pro[i].waitTime);
}
printf("\nTotal number of processes: %d\n",numProcess);
printf("Final finish time: %d\n",finaltime);
printf("Average Throughput: %.4f processes/turns\n",avgthrough);
printf("Average waiting time: %.4f units\n",avgwait);
printf("Average turnaround time: %.4f units\n", avgturn) ;
printf("Number of content switches: %d\n",cSwitch);
  
 free(pro);  //free the memory
 fclose(fp);  //close the file
  return 0;
}