#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define CRLF "\r\n"


//Program file to get the file path from a request, check if the path is valid and the mime type.


struct request{
    char fileRequested[2048];
    char method[100];
    int is_valid_path;
    
};

void get_file_path(struct request* full_request, char* request_line);
char *strrev(char *str);
char* check_mime_type (char* mime);


//read the request sent by a client and extract only the request line excluding the headers and entity body
struct request* parse_request(char* request, int length){

    struct request* request_split = malloc(sizeof(struct request));

    char request_line[2048];
    int index = 0;

    for (int i = 0;i<length;i++){

        if(request[i] == '\r' && request[i+1] == '\n'){
            
            break;
        } 
        request_line[index++] = request[i];
    }

    request_line[index] = '\0';
   
    
    get_file_path(request_split,request_line);
    return request_split;

}

// From the request line, get the method, path and http version 
// that is being used by the client and check for path escapes in the
// request path. When a path escape is found, parsing is stopped
// and the path is set to invalid. The attributes are obtained by
// counting the spaces since accoding to HTTP/1.0 spec, the request
// line always start with method followed by space followed by path followed by HTTP version.
void get_file_path(struct request* full_request, char* request_line){


    char* method =  malloc(sizeof(char) * 20);
    char* path = malloc(sizeof(char) * 2048);
    char* http_ver = malloc(sizeof(char) * 20);
    int num_spaces = 0;
    int is_valid_path = 1;

    int path_index = 0;
    int method_index = 0;
    int http_index = 0;
  
    for (int i =0; i< strlen(request_line);i++){
         
        //set path invalid
        if(request_line[i] == '/' && request_line[i+1] == '.' && request_line[i+2] == '.' &&request_line[i+3] == '/' ){
            is_valid_path = 0;
            full_request->is_valid_path = 0;
            break;
        } 
        // set path invalid
        if(request_line[i] == '/' && request_line[i+1] == '.' && request_line[i+2] == '.'  ){
            is_valid_path = 0;
            full_request->is_valid_path = 0;
            break;
        } 
        if(request_line[i]== ' '){
            num_spaces++;
             i++;
        }  

        if(num_spaces == 0){
            method[method_index++] = request_line[i];
        }

        if(num_spaces == 1  && is_valid_path == 1){
            path[path_index++] = request_line[i];     
        } 

        if(num_spaces == 2){
            http_ver[http_index++] = request_line [i];
        }

    }
   
    method[method_index] = '\0';
    path[path_index] = '\0';
    http_ver[http_index] = '\0';
 
    if(is_valid_path){
        full_request->is_valid_path =1;
    }
 
    strcpy(full_request->method,method);
    strcpy(full_request->fileRequested,path);

    free(path);
    free(method);
    free(http_ver);

}


//From the full path with no path escape, get the mime type
// First, we loop in reverse through the path and add each 
// character to an arrray until a '.' or a '\' is reached, indicating 
// that we have reached the end of the extension or the filename respectively.
// Afterwards, we loop through that array in reverse again and add each character into another array 
// to get the extension or file name in the correct order and then compare the mime type if
// it exists with known types.

char* get_mime_type(char* full_path){

	int last_index = strlen(full_path) - 1;
    
    char* mime_type =  malloc(sizeof(char)*last_index);
   memset(mime_type,0,last_index);
    int index_mime_type =0;
    for(int i = last_index;i >= 0;i--){
       
        if(full_path[i] == '/' ){
            
            break;
        }
        mime_type[index_mime_type++] = full_path[i];

        if (full_path[i] == '.'){
            break;
        }

    }
   
    mime_type[index_mime_type] = '\0';
    
    char* true_mime = strrev(mime_type);
    
    return check_mime_type(true_mime);
}

//reverse back the string
char *strrev(char *str){

     int length = strlen(str);
  
    char* mime = malloc(sizeof(char)* length + 1);
    int j =0;
     for(int i = length -1; i >=0; i--){
         
         mime[j++] = str[i];
     }

        free(str);

    mime[j] = '\0';
      return mime;
}


//compare the mime of the file requested by a client to known mime types then return the correct mime
// if it is of known type or return application/octet-stream if it is unknown.
char* check_mime_type (char* mime){

    char* html = "text/html";
     char* jpeg = "image/jpeg";
     char* css = "text/css";
     char* js =  "text/javascript";
     char* others = "application/octet-stream";
  
    if( strcmp(mime,".html") ==0){

        free(mime);
        return  html;
    }

    if(strcmp(mime,".jpg") ==0 || (strcmp(mime,".jpeg")) == 0){
      
        free(mime);
        return jpeg;

    }

    if(strcmp(mime, ".css")==0){
        free(mime);
        return css;
    }

    if(strcmp(mime,".js")==0){
        free(mime);
        return js;
    }
    free(mime);
    return others;


}