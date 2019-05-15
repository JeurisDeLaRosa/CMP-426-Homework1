//Ilham Benzekri
//Ramon Moreta De la cruz
//Eliazar Contreras
//Jeuris De la Rosa 
#include <stdlib.h>
#include <stdio.h>
#define  request 1000
#define cylind 5000
int initHead = 0;
int disk[request];


int* sortDisk()
{
   int temp = 0;
  
   for (int i = 0; i < request; ++i)
   {
       for (int j= i + 1; j < request; ++j)
       {
           if (disk[i] > disk[j])
           {
               temp = disk[i];
               disk[i] = disk[j];
               disk[j] = temp;
           }
       }
   }
   return disk;
}
int discSchedFCFS(int *ran_array)
{
   int i = 0, headMvt = 0;
   int this_start = disk[initHead];
   for (i = initHead; i < request; i++)
       headMvt += abs(disk[i] - this_start);
   for (i = 0; i < initHead; i++)
       headMvt += abs(this_start - ran_array[i]);
   //return head Mvts of FCFS
   return headMvt;
}
int discSchedSSTF(int * disk)
{
   //sort the disk
   disk = sortDisk();
   //Declare variables
   int s = initHead - 1, 
  int l = initHead + 1;
   int smallDiff = 0;
   int largeDiff = 0;
   int headMvt = 0;
   int n = request - 2;
   int newHead = initHead, headVal = disk[initHead];
   //using while loop until n=0 
 

  while (n >= 0)
   {
       largeDiff = abs(disk[l] - disk[newHead]);
       smallDiff = abs(disk[newHead] - disk[s]);


      if (smallDiff < largeDiff)
       {
           headMvt += smallDiff;
           newHead = s;
           s--;      
     }
      else
       {
           headMvt += largeDiff;
           new_head = l;
           l++;
       }
       n--;
   }

   return headMvt;
}
int discSchedSCAN(int * ranArray) {
   int currentValue = 0, i=0;
   int savedValue = disk[initHead], diff = 0;
   int headMvt = 0, curr_i = 0;
   for (i = initHead - 1; i >= 0; --i)
   {
       currentValue = disk[i];
       diff = abs(savedValue - currentValue);
       headMvt += diff;
       savedValue = currentValue;
   }

   headMvt += savedValue;
   savedValue = 0;
   for (j= initHead + 1; j< request; j++)
   {
       currentValue = disk[i];
       diff = abs(currentValue - savedValue);
       headMvt += diff;
       savedValue = currentValue;
   }
   //return t SCAN head movement 
   return headMvt;
}
int discSchedCSCAN(int *disk) {
   int n = 0;
   int currentValue = 0;
   int savedValue = disk[initHead];
   int diff = 0;
   int headMvt = 0;
   int  lastIndex = 4999;
   for (n = initHead + 1; n< request; n++)
   {
       currentValue = disk[n];
       //absolute difference value saved and current values
       diff = abs(savedValue - currentValue);
       //we add difference to the head movement
       headMvt += diff;
       //we save the current value as saved value
       savedValue = currentValue;
   }
   //add last val - upper bound, go to and
   //add zero boundary (4999)
   headMvt += lastIndex - savedValue;
   savedValue = 0;
   headMvt += 4999;
   for (i = 0; i < initHead; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(currentValue - savedValue);
       //add difference to the head movement
       headMvt += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movement of CSCAN
   return headMvt;
}
int discSchedLOOK(int* ranArray)
{
   int i = 0, currentValue = 0;
   int savedValue = disk[initHead], diff = 0;
   int headMvt = 0, curr_i = 0;
   for (i = initHead + 1; i < request; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(savedValue - currentValue);
       //add difference to the head movement
       headMvt += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   for (i = initHead - 1; i >= 0; --i)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(currentValue - savedValue);
       //add difference to the head movement
       headMvt += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movements of clocK
   return headMovement;
}
int discSchedCLOOK(int* ranArray)
{
   int i = 0, currentValue = 0;
   int savedValue = disk[initHead];
   int diff = 0;
   int headMvt = 0;
   for (i = initHead + 1; i < request; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(savedValue - currentValue);
       //add difference to the head movement
       headMvt += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   for (e = 0; e< initHead; e++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(currentValue - savedValue);
       //add difference to the head movement
       headMvt += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movement 
   return headMvt;
}
int main(int argc, char *argv[])
{
   int s = 0;
   //get initial postion from command line argument
   initialHead = atoi(argv[1]);
   if (argc != 2)
   {
       printf("The command line argument for initial head position from 0 to 4999.\n");
       return -1;
   }
   //Generate 1000 cylinder requests
   for (s= 0; s< REQUESTS; s++)
   {//Generate a random number between 1 to 5000
       disk[s] = rand() % 5000;
   }
   printf("\nThe initial position of the disk head is %d", initialHead);
   printf("\nThe value at initial head is %d\n\n", disk[initialHead]);
   printf("FCFS disk-scheduling algorithm head movements: %d\n",   discSchedFCFS(disk));
   printf("SSTF disk-scheduling: %d\n",discSchedSSTF(disk));
   printf("SCAN disk-scheduling: %d\n",discSchedSCAN(disk));
   printf("CSCAN disk-scheduling: %d\n", discSchedCSCAN(disk));
   printf("LOOK disk-scheduling algorithm head movements: %d\n", discSchedLOOK(disk));
   printf("C-LOOK disk-scheduling algorithm head movements: %d\n\n",
       discSchedCLOOK(disk));
    system("pause");   

   return 0;
}






