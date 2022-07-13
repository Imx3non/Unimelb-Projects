#ifndef ASSIGNMENT_2_FILEOPERATIONS_H
#define ASSIGNMENT_2_FILEOPERATIONS_H

#include "kdtree.h"

void query(struct kdTree* root,FILE *outputFile);
void radiusQuery(struct kdTree *root, FILE *outputFile);

void printData(struct businessData* data, FILE *outputFile, char x[], char y[]);
void printWithRadius(struct businessData* data,FILE *outputFile,  char x[], char y[], char radius[]);

void printLinkedListData(struct kdTree* root, FILE *outputFile, char x[], char y[]);
void printLinkedListDataWithRadius(struct kdTree* root, FILE *outputFile, char x[], char y[], char radius[]);
void printNotFoundWithRadius(FILE *outputFile,  char x[], char y[], char radius[]);

struct kdTree* readFile(FILE* fp,struct kdTree* root);


#endif //ASSIGNMENT_2_FILEOPERATIONS_H
