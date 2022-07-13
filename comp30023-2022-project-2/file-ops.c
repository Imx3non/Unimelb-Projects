#include <stdlib.h>
#include <stdio.h>


/*Get the contents of the file by first getting the size of the file and then malloc enough space for the file */
char* read_file(char* file_path, ssize_t* file_size){

    FILE *fp = fopen(file_path,"rb");
    
    if(fp == NULL){
        return NULL;
    }
    
    
    
    fseek(fp,0,SEEK_END);
    
    ssize_t size = ftell(fp);
//   
    *file_size = size;
    fseek(fp,0,SEEK_SET);
    
    
    char* file_contents = malloc(sizeof(char) *(size) + 1);
    if(file_contents == NULL){
      exit(EXIT_FAILURE);
    }
    memset(file_contents,0,size+1);
    fread(file_contents, 1,size,fp);
    
    
    fclose(fp);
    return file_contents;


}