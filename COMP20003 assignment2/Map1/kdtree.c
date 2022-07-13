#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "kdtree.h"
#include "FileOperations.h"

struct kdTree *insert(struct kdTree *root, struct businessData *data) {

    //printf("adding the coordinates (%f, %f)\n", data->x_coordinate, data->y_coordinate);

    if (root == NULL) {
        root = (struct kdTree *) malloc(sizeof(struct kdTree));
        assert(root);
        root->data = data;
        root->layer = 0;
        root->right = NULL;
        root->left = NULL;
        root->linkedData = NULL;
        //printf("the X coord in the struct is %f\n is a root", root->data->x_coordinate);
    }

        //check x-coord
    else if (root->layer == 0) {

        //if(root->right != NULL) root->right->layer = 1;
        // if(root->left != NULL) root->left->layer = 1;
        // printf("checking the x coord ");


        //add to the right
        if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 1) {

            //check if there is exact duplicates.
            if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                compareCoordinates(root->data->y_coordinate, data->y_coordinate == 0)) {

                // okay we add in it as a linked list.
                root = insertIntoLinkedList(root, data);
            }

                //partial match, insert to the right
            else if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                     compareCoordinates(root->data->y_coordinate, data->y_coordinate != 0)) {
                // printf("adding to the right the x-coord %f\n", data->x_coordinate );
                root->right = insert(root->right, data);
                if (root->right != NULL) root->right->layer = 1;


            } else {
                // printf("adding to the right the x-coord %f\n", data->x_coordinate );
                root->right = insert(root->right, data);
                if (root->right != NULL) root->right->layer = 1;

            }

        }

            //add to the left
        else {

            //check if there is exact duplicates
            if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                compareCoordinates(root->data->y_coordinate, data->y_coordinate == 0)) {

                root = insertIntoLinkedList(root, data);
            }

                //partial match
            else if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                     compareCoordinates(root->data->y_coordinate, data->y_coordinate != 0)) {
                //printf("adding to the left the x-coord %fn", data->x_coordinate );
                root->right = insert(root->right, data);
                if (root->right != NULL) root->right->layer = 1;


            } else {
                //printf("adding to the left the x-coord %f\n", data->x_coordinate );
                root->left = insert(root->left, data);
                if (root->left != NULL) root->left->layer = 1;

            }
        }
    }

        //check y-coord
    else {
        //printf("checking the y coord ");

        //add to the right
        if (compareCoordinates(root->data->y_coordinate, data->y_coordinate) == 1) {

            //check if there is exact duplicates.
            if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                compareCoordinates(root->data->y_coordinate, data->y_coordinate == 0)) {
                // okay we add in it as a linked list.
                root = insertIntoLinkedList(root, data);
            }
                //partial match, insert to the right
            else if (compareCoordinates(root->data->y_coordinate, data->y_coordinate) == 0 &&
                     compareCoordinates(root->data->x_coordinate, data->x_coordinate != 0)) {
                // printf("adding to the right the y-coord %f\n", data->y_coordinate );

                root->right = insert(root->right, data);
                // if(root->right != NULL) root->right->layer = 1;

            } else {
                // printf("adding to the right the y-coord %f\n", data->y_coordinate );
                root->right = insert(root->right, data);
                // if(root->right != NULL) root->right->layer = 1;
            }
        }
            //add to the left
        else {
            //check if there is exact duplicates
            if (compareCoordinates(root->data->x_coordinate, data->x_coordinate) == 0 &&
                compareCoordinates(root->data->y_coordinate, data->y_coordinate == 0)) {

                root = insertIntoLinkedList(root, data);
            }
                //partial match
            else if (compareCoordinates(root->data->y_coordinate, data->y_coordinate) == 0 &&
                     compareCoordinates(root->data->x_coordinate, data->x_coordinate != 0)) {
                // printf("adding to the left the y-coord %f\n", data->y_coordinate );
                root->right = insert(root->right, data);
                //if(root->right != NULL) root->right->layer = 1;

            } else {
                // printf("adding to the left the y-coord %f\n", data->y_coordinate );
                root->left = insert(root->left, data);
                //if(root->left != NULL) root->left->layer = 1;

            }
        }
    }

    return root;
}


int compareCoordinates(double rootCoord, double dataCoord) {

    if (fabs(dataCoord - rootCoord) < 0.0000001) return 0;
    else if (dataCoord > rootCoord) return 1;
    else return -1;
}

struct kdTree *insertIntoLinkedList(struct kdTree *root, struct businessData *data) {

    struct node *temp = (struct node *) malloc(sizeof(struct node));
    assert(temp);
    temp->data = data;
    temp->next = root->linkedData;
    root->linkedData = temp;
    return root;

}

struct kdTree* closest_root;

struct kdTree *searchQuery(struct kdTree *root, double x, double y, double *closest_distance, int *comparisons) {

    if (!root) return closest_root;
	*comparisons += 1;

    double dx = fabs(root->data->x_coordinate - x);
    double dy = fabs(root->data->y_coordinate - y);
    double D = pow(dx, 2) + pow(dy, 2);

    if (D < *closest_distance) {
        *closest_distance = D;
        closest_root = root;

    }

    if (root->layer == 0) {

        // x level
        if ((dx * dx) > *closest_distance) {
            if (x < root->data->x_coordinate)
                root = searchQuery(root->left, x, y, closest_distance, comparisons);
            else root = searchQuery(root->right, x, y, closest_distance, comparisons);
        }
        else {
            if (root->left != NULL) searchQuery(root->left, x, y, closest_distance, comparisons);
            if (root->right != NULL) searchQuery(root->right, x, y, closest_distance, comparisons);
        }
        return closest_root;
    }
    else {
        if ((dy * dy) > *closest_distance) {
            if (y < root->data->x_coordinate)
                searchQuery(root->left, x, y, closest_distance, comparisons);
            else searchQuery(root->right, x, y, closest_distance, comparisons);
        }
        else {
            if (root->left != NULL) searchQuery(root->left, x, y, closest_distance, comparisons);
            if (root->right != NULL) searchQuery(root->right, x, y, closest_distance, comparisons);
        }
        // return closest_root;
    }

    return closest_root;
}

struct kdTree *searchRadiusQuery(struct kdTree *root, double x, double y, double radius, char x_coord[], char y_coord[],
                                 char radius_s[], int *comparisons, int *found, struct kdTree *closest_root,
                                 FILE *outputFile) {

    if (!root) return closest_root;
    *comparisons += 1;
    double dx = fabs(root->data->x_coordinate - x);
    double dy = fabs(root->data->y_coordinate - y);
    double D = sqrt(pow(dx, 2) + pow(dy, 2));

    if (D <= radius) {
        *found += 1;
        closest_root = root;


        if (root->linkedData != NULL) printLinkedListDataWithRadius(root, outputFile, x_coord, y_coord, radius_s);
        else printWithRadius(root->data, outputFile, x_coord, y_coord, radius_s);

        if (root->left != NULL){
            searchRadiusQuery(root->left, x, y, radius, x_coord, y_coord, radius_s,  comparisons,
                              found, closest_root, outputFile);
        }
        if (root->right != NULL){
            searchRadiusQuery(root->right, x, y, radius, x_coord, y_coord, radius_s, comparisons,
                              found, closest_root, outputFile);
        }
    }
    else{
        if(root->layer == 0){
            if((dx*dx) > radius){
                if(x < root->data->x_coordinate) {
                    if(root->left != NULL) {
                        searchRadiusQuery(root->left, x, y, radius, x_coord, y_coord, radius_s,
                                          comparisons, found, closest_root,
                                          outputFile);
                    }
                }
                else{
                    if(root->right!= NULL){
                        searchRadiusQuery(root->right, x, y, radius, x_coord, y_coord, radius_s,
                                           comparisons, found, closest_root,
                                          outputFile);
                    }
                }
            }
            else{
                if(root->left != NULL) {
                    searchRadiusQuery(root->left, x, y, radius, x_coord, y_coord, radius_s,
                                      comparisons, found, closest_root,
                                      outputFile);
                }
                if(root->right != NULL){
                    searchRadiusQuery(root->right, x, y, radius, x_coord, y_coord, radius_s,
                                       comparisons, found, closest_root,
                                      outputFile);
                }
            }
        }
        else{
            if((dy*dy) > radius){
                if(y < root->data->y_coordinate){
                    if(root->left != NULL){
                        searchRadiusQuery(root->left, x, y, radius, x_coord, y_coord, radius_s,
                                           comparisons, found, closest_root,
                                          outputFile);
                    }
                }
                else
                if(root->right != NULL){
                    searchRadiusQuery(root->right, x, y, radius, x_coord, y_coord, radius_s,
                                       comparisons, found, closest_root,
                                      outputFile);
                }
            }
            else{
                if(root->left != NULL){
                    searchRadiusQuery(root->left, x, y, radius, x_coord, y_coord, radius_s,
                                       comparisons, found, closest_root,
                                      outputFile);
                }
                if(root->right != NULL) {
                    searchRadiusQuery(root->right, x, y, radius, x_coord, y_coord, radius_s,
                                      comparisons, found, closest_root,
                                      outputFile);
                }
            }
        }
    }
}





