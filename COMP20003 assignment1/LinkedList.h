
#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define CENSUS_YEAR 4
#define BLOCK_ID 5
#define PROPERTY_ID 7
#define BASE_PROPERTY_ID 7
#define CLUE_SMALL_AREA 128
#define TRADING_NAME 128
#define INDUSTRY_CODE 7
#define INDUSTRY_DESCRIPTION 128
#define X_COORDINATE 12
#define Y_COORDINATE 12
#define LOCATION 50
#define BUFFER_SIZE 512


struct businessData{
   char census_year[CENSUS_YEAR + 1];
    char block_id[BLOCK_ID + 1];
    char property_id[PROPERTY_ID + 1];
    char base_property_id[BASE_PROPERTY_ID + 1];
    char clue_small_area[CLUE_SMALL_AREA + 1];
    char trading_name[TRADING_NAME];
    char industry_code[INDUSTRY_CODE + 1];
    char industry_description[INDUSTRY_DESCRIPTION + 1];
    char x_coordinate[X_COORDINATE + 1];
    char y_coordinate[Y_COORDINATE + 1];
    char location[LOCATION + 1];
};

 struct node {
    struct businessData record;
    struct node* next;
};

struct data_list{
    struct node* head;
    struct node* foot;
 };


void insert(char *buffer, struct data_list *the_data);
struct data_list *create_list(struct data_list *the_data);
void delete_record(char* key, struct  data_list* the_data);
void free_dict(struct data_list* the_data);


#endif //UNTITLED_LINKEDLISH_H
