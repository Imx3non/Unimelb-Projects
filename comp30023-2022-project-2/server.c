// A simple server in the internet domain using TCP
// The port number is passed as an argument
// To compile: gcc server.c -o server
// Reference: Beej's networking guide, man pages
// Contains code from LAB9 for implementation of the server


/********************************************/
// This file contains the main function of the
// program, which reads command line inputs
// to get the protocol number, portnumber and root folder respectively.
// The program get a request from a client and returns the appropriate respone

// Rajneesh Gokool
// Student ID: 1101512
// Subject Name: Computer Systems
// Subject Code: COMP30023

/*********************************************/


#define _POSIX_C_SOURCE 200112L
#define IMPLEMENTS_IPV6
#define MULTITHREADED
#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "request-handler.c"
#include "file-ops.c"
#include "replies.c"

void *connection_handler(void *params);

void check_crlf(char *buffer, int *crlf_reached, int size);


//Struct to store the socket and the root folder.
struct thread_params
{
	char root[200];
	int socket;
};

int main(int argc, char **argv)
{
	int sockfd, newsockfd, re, s;

	struct addrinfo hints, *res;
	struct sockaddr_storage client_addr;
	socklen_t client_addr_size;

	if (argc != 4)
	{
		fprintf(stderr, "ERROR: [Protocol Number], [Port Number], [Root]\n");
		exit(1);
	}

	// char *strchr(const char *str, int c)
	int protocol = atoi(argv[1]);

	if (protocol != 4 && protocol != 6)
	{

		printf("Invalid protocol number.\n");
		exit(1);
	}

	int port = atoi(argv[3]);

	if (!(port >= 0 && port <= 65353))
	{
		printf("Invalid port number\n");
		exit(1);
	}

	// Create address we're going to listen on (with given port number)
	memset(&hints, 0, sizeof hints);
	if (protocol == 4)
	{
		hints.ai_family = AF_INET;
	}
	else
	{
		hints.ai_family = AF_INET6;
	}
	// IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;	 // for bind, listen, accept
	// node (NULL means any interface), service (port), hints, res
	s = getaddrinfo(NULL, argv[2], &hints, &res);
	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	// Create socket
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// Reuse port if possible
	re = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(int)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	// Bind address to the socket
	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		perror("setsockopt");
		exit(1);
	}
	if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	// Listen on socket - means we're ready to accept connections,
	// incoming connection requests will be queued, man 3 listen
	if (listen(sockfd, 5) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	// Accept a connection - blocks until a connection is ready to be accepted
	// Get back a new file descriptor to communicate on
	client_addr_size = sizeof client_addr;
	int *new_sock;
	while (1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_size);
		if (newsockfd < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		pthread_t* thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (thread == NULL)
		{
			exit(EXIT_FAILURE);
		}
		new_sock = malloc(1);
		*new_sock = newsockfd;
		struct thread_params *params = malloc(sizeof(struct thread_params));
		if (params == NULL)
		{
			exit(EXIT_FAILURE);
		}

		strcpy(params->root, argv[3]);
		params->socket = newsockfd;

		if (pthread_create(thread, NULL, connection_handler, (void *)params) < 0)
		{
			perror("Thread cannot be created");
			exit(1);
		}
	}
	return 0;
}

/*
	Function to handle each client connection.
	For each client, read the socket until the end and parse the request to get the file name
	Then check if the file is a valid file by checking for no presence path escapes and if that file exists on the system.
	Then get the extension of the file requested to generate the mime type.
	Finally, write a reply back to the client.
*/
void *connection_handler(void *params)
{

	struct thread_params *parameters = (struct thread_params *)(params);
	int newsockfd = parameters->socket;
	char root[200];
	strcpy(root, parameters->root);

	char buffer[2048];
	buffer[0] = '\0';
	int crlf_reached = 0;
	while (!crlf_reached)
	{
		char temp_buffer[2048];
		int x = read(newsockfd, temp_buffer, 2048);

		check_crlf(temp_buffer, &crlf_reached, x);
		strcat(buffer, temp_buffer);
		
		if (x < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		temp_buffer[x] = '\0';
	}

	int n = strlen(buffer);


	//split the request made by the client to get the path
	struct request *message_request = parse_request(buffer, n);
	if (!message_request->is_valid_path)
	{
		char *reply = create_bad_reply();
		write_socket(newsockfd, reply, strlen(reply));
		close(newsockfd);
		
	}

	//check if method is get only
	if(strcmp(message_request->method,"GET") != 0){
		char *reply = create_bad_reply();
		write_socket(newsockfd, reply, strlen(reply));
		close(newsockfd);
	}	

	//create the full path root/path-requested
	int path_requested_length = strlen(message_request->fileRequested) + strlen(root) - 1;

	char full_path[path_requested_length + 1];
	strcpy(full_path, root);

	strcat(full_path, message_request->fileRequested);

	full_path[strlen(full_path)] = '\0';
	

	char *mime_type = get_mime_type(full_path);

	ssize_t file_size = 0;

	//check if the path is valid
	if (message_request->is_valid_path)
	{
		char *file_contents = read_file(full_path, &file_size);
		char *reply;

		//check if file does not exist
		if (file_contents == NULL)
		{

			reply = create_bad_reply();
			write_socket(newsockfd, reply, strlen(reply));
			close(newsockfd);
			
		}
		else
		{

			reply = create_reply(mime_type, file_contents, file_size, newsockfd);
		}

		free(reply);
		free(message_request);
		free(file_contents);
	}
	return 0;
}


// check if the request has ended with CRLF
void check_crlf(char *buffer, int *crlf_reached, int size)
{

	if (buffer[size - 1] == '\n' && buffer[size - 2] == '\r' && buffer[size - 3] == '\n' && buffer[size - 4] == '\r')
	{

		*crlf_reached = 1;
	}
}