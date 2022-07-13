#include "dataStructure.h"

int indexFiles;
int indexProcessesFiles;
int indexIndividual;
int indexProcessids;
int indexFirstProcess;
int indexSecondProcess;


void addfiles(Structure *structure, char *disposableLine);
void countUnique(int files[], Structure *structure);
int cmpfunc(const void *a, const void *b);
void countProcess(FILE *filename, Structure *structure);
void readFile(FILE *filename, Structure *structure);
void addfiles(Structure *structure, char *disposableLine);
void countUnique(int files[], Structure *structure);
void getUniqueFiles(Structure *s);
