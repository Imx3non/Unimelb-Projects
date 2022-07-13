
#ifndef ASSIGNMENT_2_BUSINESSDATA_H
#define ASSIGNMENT_2_BUSINESSDATA_H


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
    char* census_year;
    char* block_id;
    char* property_id;
    char* base_property_id;
    char* clue_small_area;
    char* trading_name;
    char* industry_code;
    char* industry_description;
    double x_coordinate;
    double y_coordinate;
    char* location;
};

struct businessData* addRecord( char* buffer, struct businessData* data);


#endif //ASSIGNMENT_2_BUSINESSDATA_H
