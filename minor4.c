/*Author: Jorge Moreno
  Instructor: Professor Mark Thompson
  Date: 2/28/18
  Description: This program implements a simulation for the Shortest
  Remaining Time First (SRTF) scheduling algorithm. */

#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
  char processID[7];  //process id for a process
  int arrivalTime;  //arrival time for a single process
  int burstTime;  //burst time for a single process
  int waitTime;  //wait time for a single process
  int remain;  //remainging time for a single process
  int finish;  //The finish time for a single process
  int pastturn;  //the previous process that ran 
}process;

int main()
{
  int i=0; //loop variable
  int j=0;
  FILE *fp;  //The file variable for opening the file
  char fileN[40];  //holds the file name
  char tempprocessID[7];  //the temp process id for a process in the file
  int temparrivalTime;  //the temp arrival time for a process in the file
  int tempburstTime;  //the temp burst time for a process in the file
  int numProcess = 0;  //number of processes in the file
  int cSwitch = 1;  //number of context switches through the schedule algorithm
  float avgwait=0;  //The average wait times of the processes
  float avgthrough=0;  //The average throughput of the processes
  float avgturn;  //average turnaround time for the processes
  int turntime=0;  //the turntime for a single process
  int finaltime=0;  //the finaltime for every process to finish running
  int shortestR;  //holds the process with the shortest remaining time left tp run
  int turn = 0;  //used to hold each "second" that has passed 
  int waitTotal=0;  //The total wait time for every process used in calculating the average
  int count=0;  //counter to check when i need to break the main while loop
  
  printf("Please enter the filename to open.\n");  //asking the user for the filename 
  scanf("%s",fileN);
  
  fp = fopen(fileN,"r+");  //opening file with read and write permissions
  if(fp == NULL)
  {
    printf("File could not open.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("\nFile has been opened and is ready for use.\n");
    printf("Now simulating the shortest remaining time first schedule algorithm.\n");
    printf("=====================================================================");
  }
  while(!feof(fp))
  {
    fscanf(fp,"%s %d %d", tempprocessID, &temparrivalTime, &tempburstTime);  //reading in temp variables
    numProcess++;  //The number of lines in the file which also means the number of processes in the file
  }

  process *pro = malloc(numProcess *sizeof(process));  //allocating dynamic array of my structures with the number of processes as the size
  fseek(fp,0,SEEK_SET);  //returning the file pointer to the beginning
  for(i=0;i<numProcess;i++)
{
  fscanf(fp,"%s %d %d", pro[i].processID,&pro[i].arrivalTime,&pro[i].burstTime);  //reading in the real variables
}
  printf("\nProcessID, Arrival time, and Burst times for each process in the file\n");
for(i=0;i<numProcess;i++)
{
  printf("%s %d %d\n", pro[i].processID,pro[i].arrivalTime,pro[i].burstTime);  //make sure i got the correct values from the file
}
printf("=====================================================================");

for(i=0;i<numProcess;i++)  
{
 pro[i].remain =0;    //Setting the initial remain times for each process to 0
 finaltime += pro[i].burstTime;  //Finding what the finaltime will be
}
 
while(1)
{
  if(turn > 0)  //If this is not the first turn loop
  {
   for(i=0;i<numProcess;i++)  //setting each process previous time to their remaining time
   {
    pro[i].pastturn = pro[i].remain;
   }
  }
  
  for(i=0;i<numProcess;i++)  //setting each process remain time to their burst time
  {
   if(turn == pro[i].arrivalTime)
   {
    pro[i].remain = pro[i].burstTime;
    cSwitch++;  //incremnt the context switch count
   }
  }
 for(i=0;i<numProcess;i++)
 {
  if(pro[i].remain !=0)
  {
    turntime++;  //if there is still remaining time in any process increment the turntime
  }
 }
 shortestR =j;
 while(pro[shortestR].remain == 0)  //loop until we find a process that is not 0
 {
   j++;
   shortestR=j;
 }
 for(i=0;i<numProcess;i++)  //find which process has the shortest remain
 {
   if(pro[i].remain < pro[shortestR].remain && pro[i].remain > 0)
   {
     shortestR = i;
   } 
 }
 pro[shortestR].remain--;  //now we decrement the processes remain time by one
 turn++;
  for(i=0;i<numProcess;i++)  //keep track of the processes that are waiting and increase their wait time
  {
    if(pro[i].remain > 0 && i != shortestR)
    {
        pro[i].waitTime++;
        waitTotal++;
    }
  }
  for(i=0;i<numProcess;i++)  //checks if a process has finished
  {
    if(pro[i].pastturn == 1 && pro[i].remain == 0)
    {
       pro[i].finish = turn;
    }
  }
  for(i=0;i<numProcess;i++)
  {
    if(pro[i].remain == 0)
    {
      count++;  //if there is no remaining time in a process increment count
    }
  }
  if(count == numProcess) 
  {
    break;  //When none of the processes have remaining time, break the loop
  }
  count = 0;
}
avgthrough = (float)numProcess / (float)turn;  //Finding the average throughput
avgwait = (float)waitTotal / (float)numProcess;  //Finding the average wait time
avgturn = (float)turntime / (float)numProcess;  //Finding the average turnaround time
printf("\n-----------------------------------------------\n");
printf("PID   Arrive   Burst   Remain   Finish   Wait |\n");
printf("-----------------------------------------------\n");
for(i=0;i<numProcess;i++)  //printing out all the processes and information
{
  printf("%s  %5d    %5d    %5d    %5d   %5d  |\n",pro[i].processID,pro[i].arrivalTime,pro[i].burstTime,pro[i].remain,pro[i].finish,pro[i].waitTime);
}
printf("-----------------------------------------------\n");
printf("\n> Total number of processes: %d\n",numProcess);
printf("> Final finish time: %d\n",finaltime);
printf("> Average Throughput: %.4f processes/turns\n",avgthrough);
printf("> Average waiting time: %.4f units\n",avgwait);
printf("> Average turnaround time: %.4f units\n", avgturn) ;
printf("> Number of content switches: %d\n",cSwitch);
printf("=====================================================================\n");
  
 free(pro);  //free the memory for the dynamically allocated pro pointer
 fclose(fp);  //close the file
  
 return 0;
}