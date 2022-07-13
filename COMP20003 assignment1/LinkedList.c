#include "LinkedList.h"

struct node *add_record(struct node *new, char *buffer);

struct data_list *create_list(struct data_list *the_data) {

    /*Create an empty struct to store the data*/

    struct data_list *list;
    list = (struct data_list *) malloc(sizeof(*list));
    assert(list != NULL);
    list->foot = list->head = NULL;
    return list;

}

void insert(char *buffer, struct data_list *the_data) {

    /*Insert each record in the linked_list*/

    struct node *new;
    new = (struct node *) malloc(sizeof(struct node));
    assert(new != NULL);

    add_record(new, buffer);
	
    new->next = NULL;

    if (the_data->foot == NULL) {
		
        the_data->head = the_data->foot = new;

    } else {
        the_data->foot->next = new;
        the_data->foot = new;
    }
}

struct node *add_record(struct node *new, char *buffer) {
	
	/*Function to add each record in their respective datafield by keeping track of the commas. */

    int i = 0;
    int comma_count = 0;

    // A variable for each data field.
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, k = 0, l = 0, m = 0;

    //keeep track of the " in these data fields.
	int punct_count_trading = 0;
    int punct_count_industry_description = 0;
    int punct_count_location = 0;
	
	//temporary arrays to keep the data fields record.
    char year[CENSUS_YEAR + 50], block_id[BLOCK_ID + 50], property_id[PROPERTY_ID + 50],
            base_property_id[BASE_PROPERTY_ID + 50], clue[CLUE_SMALL_AREA + 50], trading_name[TRADING_NAME + 50],
            industry_code[INDUSTRY_CODE + 50], industry_description[INDUSTRY_DESCRIPTION + 50],
            x_coord[X_COORDINATE + 50], y_coord[Y_COORDINATE + 50], location[LOCATION + 50];
	
	
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
			
			/*this is where we can have a , or " in a record*/
			
			//this is where the record starts and we skip the first "
			if(buffer[i] == '\"' && punct_count_trading == 0) {punct_count_trading++; i++;}
			
			//we add until we reach the next "
			else if(punct_count_trading == 1){
				
				//check if we reached the next "
				if(buffer[i] == '\"') punct_count_trading++;
				else{
					trading_name[f++] = buffer[i++];
				}
			}
			
			//this means that the record contains , and we skip the " and , 
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
			
			//okay we add the last character and we skip to the next record field.
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
	
	//add to the linked list
    strcpy(new->record.census_year, year);
    strcpy(new->record.block_id, block_id);
    strcpy(new->record.property_id, property_id);
    strcpy(new->record.base_property_id, base_property_id);
    strcpy(new->record.clue_small_area, clue);
    strcpy(new->record.trading_name, trading_name);
    strcpy(new->record.industry_code, industry_code);
    strcpy(new->record.industry_description, industry_description);
    strcpy(new->record.x_coordinate, x_coord);
    strcpy(new->record.y_coordinate, y_coord);
    strcpy(new->record.location, location);
	return new;

}

void delete_record(char *key, struct data_list *the_data) {
    struct node *current = the_data->head;
    struct node *temp;

    while (current != NULL) {
        if (strcmp(current->record.trading_name, key) == 0) {
            temp = current;
            current = current->next;
            free(temp);

        } else {
            current = current->next;
        }
    }
}

void free_dict(struct data_list *the_data) {
    struct node *current = the_data->head;
    struct node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(the_data);
}


