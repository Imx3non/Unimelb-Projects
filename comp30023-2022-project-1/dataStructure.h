/*
A data structure to store:
    1. Each line from the files
    2. For each process, its respective files locked and requested
    3. number of processes 
    4. number of files present 
    5. number of unique files
    6. array of the fist file of processes
    7. array of the second file of processes
    9. array of unique files sorted in ascending order
    10. array of process ids only

    11. A mapping that maps each lines to the corrected index based on the order the are read from the text file.

*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct Mapping{
    int fileid;
}Mapping;


typedef struct dataStructure
{
    char** individualProcessFiles;
    char** processAndFiles;
    unsigned int numProcesses;
    int* allFiles;
    int* processFirstFile;
    int* processSecondFile;
    char** processids;
    unsigned int numFiles;
    unsigned int numUniqueFiles;
    int* uniqueFiles;
    
    Mapping** map;


} Structure;










