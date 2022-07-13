
#ifndef ASSIGNMENT_2_KDTREE_H
#define ASSIGNMENT_2_KDTREE_H
#include "BusinessData.h"
#include <stdio.h>

struct node{
    struct businessData* data;
    struct node* next;
};

struct kdTree{
    struct businessData* data;
    struct kdTree* left;
    struct kdTree* right;
    struct node* linkedData;
    int layer; // split dimension 0 is x dim and 1 is y dim

};

int compareCoordinates(double rootCoord, double dataCoord);
int maxDepth (struct kdTree* root);

struct kdTree* createRoot(struct kdTree* root);
struct kdTree* insertIntoLinkedList(struct kdTree* root, struct businessData* data);
struct kdTree* insert(struct kdTree *root, struct businessData *data);
struct kdTree* search(struct kdTree* root, double x, double y, int* comparisons, FILE* outputFile);
struct kdTree* searchQuery(struct kdTree* root, double x, double y, double *current_distance,  int* comparisons);
struct kdTree *searchRadiusQuery(struct kdTree *root, double x, double y, double radius, char x_coord[], char y_coord[],
                                 char radius_s[], int *comparisons, int *found, struct kdTree *closest_root,
                                 FILE *outputFile);


#endif //ASSIGNMENT_2_KDTREE_H
