#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "socket_ops.c"
#define REPLY200 "HTTP/1.0 200 OK\r\n"
#define REPLY400 "HTTP/1.0 404 Not Found\r\n"
#define CONTENT "Content-type: "
#define LENGTH "Content-length: "


/*
    create a the status 200 resonse by writing the status line then the headers and then the entity body.
*/
char *create_reply(char *mime_type, char *file_contents, ssize_t file_size, int socket)
{

    

    char size_string[30];
    sprintf(size_string, "%ld", file_size);
    

    int reply_length = strlen(REPLY200) + strlen(CONTENT) + strlen(mime_type) + strlen("\r\n") + strlen(LENGTH) +
                       strlen(size_string) + strlen("\r\n\r\n") + file_size;

    char *reply = malloc(sizeof(char) * reply_length);

    write_socket(socket, REPLY200, strlen(REPLY200));

    write_socket(socket, CONTENT, strlen(CONTENT));

    write_socket(socket, mime_type, strlen(mime_type));

    write_socket(socket, "\r\n", strlen("\r\n"));

    write_socket(socket, LENGTH, strlen(LENGTH));

    write_socket(socket, size_string, strlen(size_string));

    write_socket(socket, "\r\n\r\n", strlen("\r\n\r\n"));

    if (file_contents != NULL)
    {

        
        write_socket(socket, file_contents, file_size);
        
    }

    return reply;
}

/*
return the 404 status line
*/
char *create_bad_reply()
{

    char *reply = malloc(sizeof(char) * sizeof(REPLY400));
    strcpy(reply, REPLY400);

    return reply;
}