#include "LinkedList.h"

void print_test(struct data_list *data_list);

void read_file(FILE *fp, struct data_list *the_data);

void read_keys(struct data_list *, FILE *output_file);

void search_key(struct data_list *the_data, char *key, FILE *output_file);

void write_key(struct node *current, FILE *output_file);

int main(int argc, char **argv) {

    //create the struct
    struct data_list *the_data;
    the_data = create_list(the_data);

    FILE *fp = fopen(argv[1], "r");
    assert(fp != NULL);
    read_file(fp, the_data);

    fclose(fp);

    FILE *output_file = fopen(argv[2], "w");
    assert(output_file != NULL);
    read_keys(the_data, output_file);
	
    fclose(output_file);
    free_dict(the_data);


}


void read_file(FILE *fp, struct data_list *the_data) {

    /*Function to read the csv file*/

    char buffer[BUFFER_SIZE];
  

    //get the headings
    fgets(buffer, BUFFER_SIZE, fp);

    //get the data and add it to the linked list
    while ((fgets(buffer, BUFFER_SIZE, fp)) != NULL) {
        insert(buffer, the_data);
    }

}

void read_keys(struct data_list *the_data, FILE *output_file) {

    /*Function to read the keys from the key file.*/

    char key[TRADING_NAME];


    while (fgets(key, TRADING_NAME, stdin) != NULL) {


        int i = strlen(key);
        /* Since fgets also take \n we remove it from the key*/

        if (key[i - 1] == '\n') {
            key[i - 1] = '\0';
        }

        search_key(the_data, key, output_file);
    }


}


void search_key(struct data_list *the_data, char *key, FILE *output_file) {

    /*Function to search the linked list for the keys */

    struct node *current = the_data->head;
    int keys_found = 0;

    while (current != NULL) {
       
        if (strcmp(current->record.trading_name, key) == 0) {

            keys_found++;
            write_key(current, output_file);
            current = current->next;

        } else {
            current = current->next;
        }

    }
    if (keys_found == 0) {

        fprintf(output_file, "%s --> NOT FOUND\n", key);
    }

}

void write_key(struct node *current, FILE *output_file) {

    /*Function to  Write the keys in file*/

    fprintf(output_file,
            "%s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",
            current->record.trading_name, current->record.census_year, current->record.block_id,
            current->record.property_id, current->record.base_property_id,
            current->record.clue_small_area, current->record.industry_code, current->record.industry_description,
            current->record.x_coordinate, current->record.y_coordinate,
            current->record.location);

}



