/*

This file contains all of the functions that manipulates the datastructure 
It includes functions to malloc the structure
Calculate the execution time 
Check for deadlocks

Rajneesh Gokool
Student ID: 1101512
Subject Name: Computer Systems
Subject Code: COMP30023


*/


#include "dataStructure.h"
#include "util.c"
#include <stdlib.h>

void calculateExecution(int *secondFiles, int index);



/*
Allocate the exact space by that is requried by the structure to hold the system after counting the number of process lines
*/
void allocateSpace(Structure *s){

    s->numFiles = s->numProcesses * 2;

    s->processAndFiles = malloc(sizeof(char *) * s->numProcesses);
    s->individualProcessFiles = malloc(sizeof(char *) * s->numProcesses);
    s->processids = malloc(sizeof(char *) * s->numProcesses);
    s->individualProcessFiles = malloc(sizeof(char *) * s->numProcesses);
    s->processids = malloc(sizeof(char *) * s->numProcesses);
    s->allFiles = malloc(sizeof(int) * s->numFiles);
    s->processFirstFile = malloc(sizeof(int) * s->numProcesses);
    s->processSecondFile = malloc(sizeof(int) * s->numProcesses);

}

// allocte the space requried by the structure to store the inital process lines and initalise the number of process and files to 0 initially.
void initialAllocation(Structure *s){

    s->processAndFiles = malloc(sizeof(char **));
    assert( s->processAndFiles!=NULL);

    s->individualProcessFiles = malloc(sizeof(char **));
    assert( s->individualProcessFiles!= NULL);

    s->processids = malloc(sizeof(char **));
    assert(s->processids!= NULL);

    s->numFiles = 0;   
    s->numProcesses = 0;
}

void freeStructure(Structure *s){

    for(int i = 0; i < s->numProcesses; i ++){

        free(s->processAndFiles[i]);
        free(s->processids[i]);
        free(s->individualProcessFiles[i]);
       
    }
   
    free(s->processAndFiles);
    free(s->processids);
    free(s->individualProcessFiles);
    free(s->processFirstFile);
    free(s->processSecondFile);


    free(s->allFiles);
    free(s->map);
    free(s->uniqueFiles);

}


//Function that map the fileID into the same index
void createMapping(int *uniqueFiles,Structure *s){


    s->map= malloc(sizeof(Mapping*) * s->numUniqueFiles);
    assert(s->map != NULL);

        for(int i = 0; i < s->numUniqueFiles; i++){
           s->map[i] = malloc(sizeof(Mapping)); 
           assert(s->map[i]!= NULL);
           s->map[i]->fileid = uniqueFiles[i];

        }

 }

//used by the adjacency list to get the index to where a fileId vertex is supposed to be 
//placed in the adjacency list
int getIndex(Structure *s, int src){

    for(int i = 0; i < s->numUniqueFiles;i++){

        int currentFile = s->map[i]->fileid;
        if(currentFile == src) return i;
    }
    return 0;

}

//return the fileid that needs to be stored in the adjacency list from the latter's index
int getFile(int index, Structure *s){

    return s->map[index]->fileid;
}


//variable to store the total execution time
int time = 0;


/*
    Function to calculate the execution time if being asked.

    At t =0 all the first files of each process will be executed and hence, the focus is only on 
    the the second files of each process.

    To calulate the subsequent execution times:
    1.The second files are put in an array that is then sorted so as duplicates will be next to each other
    2.The execution time is then calculated with the calculateExecution() function.
*/
int getExecution(Structure *s)
{


    int secondFiles[s->numProcesses];

    for (int i = 0; i < s->numProcesses; i++)
    {

        secondFiles[i] = s->processSecondFile[i];
    }

    // sort second files for easy calculation of the process files

    qsort(secondFiles, s->numProcesses, sizeof(int), cmpfunc);
    calculateExecution(secondFiles, s->numProcesses);

    return time;
}

/*
    To calculate the execution time, 3 variables are used has helpers:
    1. numMinusOne that count the number of -1 reached so far in the sorted second process files array.
        an index that is marked as -1 implies that is has already been counted in an execution.
    2. a tmp variable to check if the next file in the array is marked with a -1 or is greater than the current one.
    3. a numSecondFiles which when numMinusOne == numSecondFiles implies that all the files has been allocated a time slot

    The algorithm is as follows:
    1. While the number of -1 < numSecondFiles
    
    2. create a tmp variable with -1

    3. loop through the sorted files array and check if tmp == secondFiles[i] which implies that they are duplicates
        or if secondFiles[i] == -1 which implies file has already been added to a timeslot. Skip that iteration if true
    
    4.  if secondFiles[i] > tmp this means that a file that is unmarked by -1 and is not a duplicate has been found
        and can be added to the same timeslot as the previous file to it that was not a duplicate.

    5. mark the file with a -1 and continue the iteration through the array.

    6. After the full iteration over the array, the time variable is incremented as all the files that are not duplicates has 
        been given a time slot and files that has not been allocated will be in the next time slot.

    7. Then if the numMinusOne != numSecondFiles iterate over the the array again (step 3) as there are still files with unallocated times slot

    8. When numMinusOne == numSecondFiles while loop stops and time is incremented again to account for the releasing of the files that were 
       last allocated.

*/
void calculateExecution(int *secondFiles, int numSecondFiles)
{

    int numMinusOne = 0;

    while (numMinusOne != numSecondFiles)
    {
        int tmp = -1;

        for (int i = 0; i < numSecondFiles; i++)
        {

            if (tmp == secondFiles[i] || secondFiles[i] == -1)
            {
                continue;
            }

            if (secondFiles[i] > tmp)
            {
                tmp = secondFiles[i];
                secondFiles[i] = -1;
                numMinusOne++;
            }
        }
        time++;
    }
    time++;
    printf("Execution time %d\n",time);
}


/*
    Function to calculate if a deadlock is present in the system.

    In order to check for deadlock:
    1. loop through all the processes and get the second file of a process line (file2)
    2. loop through all the processes again and check if the first file of any process
       matches file2. If yes then deadlock is detected.
    
*/
int checkDeadlock(Structure *s)
{

    for (int i = 0; i < s->numProcesses; i++)
    {

        char line1[40];
        strcpy(line1, s->individualProcessFiles[i]);

        //get the second file of a process line
        char *waitingToLock = strtok(line1, " ");
        waitingToLock = strtok(NULL, " ");

        //loop through the process line again from i + 1 since there is no need to start from index i (current to bottom) 
        for (int j = i + 1; j < s->numProcesses; j++)
        {


            char line2[40];
            strcpy(line2, s->individualProcessFiles[j]);

            //get first file
            char *currentlyLocked = strtok(line2, " ");

            //deadlock found
            if (strcmp(waitingToLock, currentlyLocked) == 0)
                return 1;

            
        }

        //loop from top to current index i since the deadlock could occur there as well
        for (int k = 0; k < i; k++)
            {

                if (i == 0)
                    continue;
                char line2[40];
                strcpy(line2, s->individualProcessFiles[k]);

                //get first file
                char *currentlyLocked1 = strtok(line2, " ");

                //deadlock found
                if (strcmp(waitingToLock, currentlyLocked1) == 0)
                {
                    return 1;
                }
            }
    }

    //deadlock not found
    return 0;
}


