/*
This file contains functions that does reads the text file and add each process line in the file structure


Rajneesh Gokool
Student ID: 1101512
Subject Name: Computer Systems
Subject Code: COMP30023

*/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructure.c"


int indexFiles = 0;
int indexProcessesFiles = 0;
int indexIndividual = 0;
int indexProcessids = 0;
int indexFirstProcess = 0;
int indexSecondProcess = 0;


void addfiles(Structure *structure, char *disposableLine);
void countUnique(int files[], Structure *structure);
int cmpfunc(const void *a, const void *b);

void countProcess(FILE *filename, Structure *structure)
{

    char line[50];

    while (fgets(line, 50, filename))
    {

        if (strlen(line) <= 1)
            break;

        structure->numProcesses++;
    }
}

void readFile(FILE *filename, Structure *structure)
{

    char line[50];
    while (fgets(line, 50, filename))
    {

        char *token = strtok(line, "\n");
        structure->processAndFiles[indexProcessesFiles] = malloc(sizeof(char) * strlen(line));
        assert(structure->processAndFiles[indexProcessesFiles] != NULL);

        strcpy(structure->processAndFiles[indexProcessesFiles++], token);

        char discardableLine[strlen(token)];

        strcpy(discardableLine, token);
        addfiles(structure, discardableLine);
    }
    
    
    qsort(structure->allFiles, structure->numFiles, sizeof(int), cmpfunc);
    countUnique(structure->allFiles, structure);
}

void addfiles(Structure *structure, char *disposableLine)
{

    char *processid = strtok(disposableLine, " ");
    char *file1 = strtok(NULL, " ");
    char *file2 = strtok(NULL, " ");

    structure->processids[indexProcessids] = malloc(sizeof(char) * strlen(processid));
    assert(structure->processids[indexProcessids] != NULL);
    strcpy(structure->processids[indexProcessids++], processid);

    int lengthLine = strlen(file1) + strlen(file2) + 1;

    structure->individualProcessFiles[indexIndividual] = malloc(sizeof(char) * lengthLine);\
    assert(structure->individualProcessFiles[indexIndividual] != NULL);
    strcpy(structure->individualProcessFiles[indexIndividual], file1);
    strcat(structure->individualProcessFiles[indexIndividual], " ");
    strcat(structure->individualProcessFiles[indexIndividual++], file2);

    structure->processFirstFile[indexFirstProcess++] = atoi(file1);
  
    structure->allFiles[indexFiles++] = atoi(file1);
    structure->processSecondFile[indexSecondProcess++] = atoi(file2);
    structure->allFiles[indexFiles++] = atoi(file2);

}



void countUnique(int files[], Structure *structure)
{
    
    int tmp = files[0];
    structure->numUniqueFiles = 1;

    
    for (int i = 0; i < indexFiles; i++)
    {

        if (tmp == files[i])
        {
            continue;
        }
        structure->numUniqueFiles++;

        tmp = files[i];
    }
}


void getUniqueFiles(Structure *s){

    s->uniqueFiles = malloc(sizeof(int)* s->numUniqueFiles);
    assert(s->uniqueFiles != NULL);
    int indexUnique = 0;

    int tmp = -1;
    for(int i = 0; i < s->numFiles; i++){
      
        if(s->allFiles[i] > tmp){
            tmp = s->allFiles[i];
           s->uniqueFiles[indexUnique++] = tmp;
          
        }

    }

   createMapping(s->uniqueFiles,s );
}


