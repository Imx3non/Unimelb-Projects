#include "BusinessData.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


struct businessData* addRecord(char* buffer, struct businessData* data){

    /*Function to add each  in their respective datafield by keeping track of the commas. */

    int i = 0;
    int comma_count = 0;

    // A variable for each data field.
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, k = 0, l = 0, m = 0;

    //keeep track of the " in these data fields.
    int punct_count_trading = 0;
    int punct_count_industry_description = 0;
    int punct_count_location = 0;

    //temporary arrays to keep the data fields .
    char year[CENSUS_YEAR + 50], block_id[BLOCK_ID + 50], property_id[PROPERTY_ID + 50],
            base_property_id[BASE_PROPERTY_ID + 50], clue[CLUE_SMALL_AREA + 50], trading_name[TRADING_NAME + 50],
            industry_code[INDUSTRY_CODE + 50], industry_description[INDUSTRY_DESCRIPTION + 50],
            x_coord[X_COORDINATE + 50], y_coord[Y_COORDINATE + 50], location[LOCATION + 50];
    // printf("test1\n");


    //Loop through The buffer
    while(buffer[i] != '\0'){


        if(comma_count == 0){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                year[a++] = buffer[i++];
            }
        }

        else if(comma_count == 1){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                block_id[b++] = buffer[i++];
            }
        }

        else if(comma_count == 2){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                property_id[c++] = buffer[i++];
            }
        }

        else if (comma_count == 3){
            if(buffer[i] == ',') {i++; comma_count++;}
            else {
                base_property_id[d++] = buffer[i++];
            }
        }
        else if (comma_count == 4){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                clue[e++] = buffer[i++];
            }
        }
        else if (comma_count == 5){

            /*this is where we can have a , or " in a */

            //this is where the  starts and we skip the first "
            if(buffer[i] == '\"' && punct_count_trading == 0) {punct_count_trading++; i++;}

                //we add until we reach the next "
            else if(punct_count_trading == 1){

                //check if we reached the next "
                if(buffer[i] == '\"') punct_count_trading++;
                else{
                    trading_name[f++] = buffer[i++];
                }
            }

                //this means that the  contains , and we skip the " and ,
            else if(punct_count_trading == 2 && buffer[i+1] != '\"'){

                i+=2; comma_count++;
            }

                //this is the case where there is a " in the name. We skip it and add the next character.
            else if(punct_count_trading == 2 && buffer[i+1] == '\"'){
                i++;
                trading_name[f++] = buffer[i++];
                punct_count_trading++;
            }

                //continue to add unitl we reach the last " which signifies the end of the data field
            else if(punct_count_trading == 3 && buffer[i] != '\"'){
                trading_name[f++] = buffer[i++];
            }

                //okay we add the last character and we skip to the next  field.
            else if(punct_count_trading == 3 && buffer[i] == '\"'){
                trading_name[f] = buffer[i];
                f++;
                i+=4;
                comma_count++;
            }

                //No , or " in the data field
            else{
                if(buffer[i] == ',') {i++; comma_count++;}
                else{
                    trading_name[f++] = buffer[i++];
                }
            }
        }

        else if(comma_count == 6){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                industry_code[g++] = buffer[i++];
            }
        }


            //do the same thing as for comma_count == 5 but no need to check for " in the data field
        else if (comma_count == 7){
            if(buffer[i] == '\"' && punct_count_industry_description == 0){
                i++; punct_count_industry_description++;
            }
            else if(punct_count_industry_description == 1){
                if(buffer[i] == '\"') punct_count_industry_description++;
                else{
                    industry_description[h++] = buffer[i++];
                }
            }
            else if(punct_count_industry_description == 2){
                i+=2; comma_count++;
            }
            else{
                if(buffer[i] == ',') {i++; comma_count++;}
                else{
                    industry_description[h++] = buffer[i++];
                }
            }
        }

        else if(comma_count == 8){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{

                x_coord[k++] = buffer[i++];
                //printf("%c",x_coord[k]);
            }
        }

        else if(comma_count == 9){
            if(buffer[i] == ',') {i++; comma_count++;}
            else{
                y_coord[l++] = buffer[i++];
            }
        }

            //do the same thing as for comma_count == 5 but no need to check for " in the data field
        else if(comma_count == 10){
            if(buffer[i] == '\"' && punct_count_location == 0){
                punct_count_location++; i++;
            }
            else if(punct_count_location == 1){
                if(buffer[i] == '\"') punct_count_location++;
                else{
                    location[m++] = buffer[i++];
                }
            }

            else if(punct_count_location == 2){
                i+=2; comma_count++;
            }
            else{
                if(buffer[i] == ',') {i++; comma_count++;}
                else{
                    location[m++] = buffer[i++];
                }
            }
        }

        else{
            i++;
        }
    }

    //printf("test2\n");

    /*terminates all the strings with a null byte*/

    year[a] = '\0';
    block_id[b] = '\0';
    property_id[c] = '\0';
    base_property_id[d] = '\0';
    clue[e] = '\0';
    trading_name[f] = '\0';
    industry_code[g] = '\0';
    industry_description[h] = '\0';
    x_coord[k] = '\0';
    y_coord[l] = '\0';
    location[m] = '\0';
    //printf("%s\n", x_coord);

    // double x = atof(x_coord);
    // printf("%f\n",x);



    //add to the linked list
    double x = atof(x_coord);
    double y = atof(y_coord);
    //printf("test3\n");


    data->census_year =(char*)malloc(sizeof(year)) ;
    data->block_id = (char*)malloc(sizeof(block_id)) ;
    data->property_id = (char*)malloc(sizeof(property_id)) ;
    data->base_property_id = (char*)malloc(sizeof(base_property_id)) ;
    data->clue_small_area = (char*)malloc(sizeof(clue)) ;
    data->trading_name =(char*)malloc(sizeof(trading_name))  ;
    data->industry_code = (char*)malloc(sizeof(industry_code)) ;
    data->industry_description = (char*)malloc(sizeof(industry_description)) ;
    data->location = (char*)malloc(sizeof(location)) ;

    strcpy(data->census_year, year);
    strcpy(data->block_id, block_id);
    strcpy(data->property_id, property_id);
    strcpy(data->base_property_id, base_property_id);
    strcpy(data->clue_small_area, clue);
    strcpy(data->trading_name, trading_name);
    strcpy(data->industry_code, industry_code);
    strcpy(data->industry_description, industry_description);
    data->x_coordinate = x;
    data->y_coordinate = y;
    strcpy(data->location, location);


//    printf("the year stored in struct is %s \n", data->census_year);
//    printf("the block id stored in struct is %s\n", data->block_id);
//    printf("the property id stored in struct is %s\n", data->property_id);
//    printf("the base property id stored in struct is %s\n", data->base_property_id);
//    printf("the clue small area stored in struct is %s\n", data->clue_small_area);
//    printf("the trading name stored in struct is %s\n", data->trading_name);
//    printf("the industry code stored in the struct is %s\n", data->industry_code);
//    printf("the industry description stored in the struct is %s\n", data->industry_description);
//    printf("the X coord in the struct is %f\n", data->x_coordinate);
//    printf("the y coord in the struct is %f\n",data->y_coordinate);
//    printf("the location coord in the struct is %s\n", data->location );
    return data;
}
