#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//Function to write a message to a socket
int  write_socket(int socket, char* reply, size_t size){

    
    int n = write(socket,reply,size);
    
    if (n < 0) {
		perror("write");
		exit(EXIT_FAILURE);
	}
    return n;
}