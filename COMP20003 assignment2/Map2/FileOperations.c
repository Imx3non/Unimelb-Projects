#include "FileOperations.h"
#include <string.h>
#include <stdlib.h>

#define NOT_FOUND "NOTFOUND"

struct kdTree *readFile(FILE *fp, struct kdTree *root) {

    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, fp);
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      
        struct businessData *data = (struct businessData *) malloc(sizeof(struct businessData));
        data = addRecord(buffer, data);
        root = insert(root, data);

    }
    return root;
}

void printData(struct businessData *data, FILE *outputFile, char x[], char y[]) {


    fprintf(outputFile, "%s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || "
                        "CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s"
                        " || Industry (ANZSIC4) description: %s ""|| x coordinate: %f || y coordinate: %f"
                        " || Location: %s ||\n\n", x, y, data->census_year,
            data->block_id, data->property_id, data->base_property_id,
            data->clue_small_area, data->trading_name, data->industry_code,
            data->industry_description, data->x_coordinate, data->y_coordinate,
            data->location);
    
}

void printLinkedListData(struct kdTree *root, FILE *outputFile, char x[], char y[]) {

    struct node *linkedData = root->linkedData;
    while (1) {
        //add to file
        if (linkedData == NULL) break;
        printData(linkedData->data, outputFile, x, y);
        linkedData = linkedData->next;
    }
}
void printLinkedListDataWithRadius(struct kdTree* root, FILE *outputFile, char x[], char y[], char radius[]){
    struct node *linkedData = root->linkedData;
    while (1) {
        //add to file
        if (linkedData == NULL) break;
        printWithRadius(linkedData->data, outputFile, x, y,radius);
        linkedData = linkedData->next;
    }
}

void printNotFoundWithRadius(FILE *outputFile, char x[], char y[], char radius[]) {
    fprintf(outputFile, "%s %s %s --> %s\n", x, y, radius, NOT_FOUND);
}

void printWithRadius(struct businessData* data,FILE *outputFile,  char x[], char y[], char radius[]){

    fprintf(outputFile, "%s %s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || "
                        "CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s"
                        " || Industry (ANZSIC4) description: %s ""|| x coordinate: %f || y coordinate: %f"
                        " || Location: %s ||\n\n", x, y, radius, data->census_year,
            data->block_id, data->property_id, data->base_property_id,
            data->clue_small_area, data->trading_name, data->industry_code,
            data->industry_description, data->x_coordinate, data->y_coordinate,
            data->location);
}


void query(struct kdTree *root, FILE *outputFile) {

    char buffer[50];
    char x[20];
    char y[20];
    
    while (fgets(buffer, 50, stdin) != NULL) {
        int comparisons = 0;

        strcpy(x, strtok(buffer, " "));
        strcpy(y, strtok(NULL, " "));

         for (int i = 0; i < strlen(y); ++i) {
            if(y[i] == '\r' || y[i] == '\n') y[i] = '\0';
        }
        double closest_distance = 100000000000000;
        struct kdTree *data_root =searchQuery(root, atof(x), atof(y), &closest_distance, &comparisons);
       
        printf("%s %s --> %d\n", x, y, comparisons);

        if (data_root->linkedData != NULL) {

            printData(data_root->data, outputFile, x, y);
            printLinkedListData(data_root, outputFile, x, y);
        }
        else printData(data_root->data, outputFile, x, y);

    }
}

void radiusQuery(struct kdTree *root, FILE *outputFile) {
	//search the radius query 
    char buffer[50];
    char x[20];
    char y[20];
    char radius[20];
   

    while (fgets(buffer, 50, stdin) != NULL) {
		

        int comparisons = 0;
        int found = 0;
        strcpy(x, strtok(buffer, " "));
        strcpy(y, strtok(NULL, " "));
        strcpy(radius, strtok(NULL, " "));

        for (int i = 0; i < strlen(radius); ++i) {
            if(radius[i] == '\r' || radius[i] == '\n') radius[i] = '\0';
        }
        searchRadiusQuery(root,atof(x),atof(y),atof(radius),x,y,radius,&comparisons,&found,root,outputFile);
        printf("%s %s %s --> %d \n", x, y, radius, comparisons);
        if(!found){
            printNotFoundWithRadius(outputFile,x,y,radius);
        }
    }
}
