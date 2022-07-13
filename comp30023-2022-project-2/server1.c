// select-server.c -- a cheezy multiperson chat server
// For Q1.1

#define _POSIX_C_SOURCE 200112L
#define IMPLEMENTS_IPV6
#define MULTITHREADED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>

#define PORT "8080"
#include "request-handler.c"
#include "file-ops.c"
#include "replies.c"

struct clients{
	int socket;
	char buffer[2048];
	int crlf_reached;
	int buffer_size;
	struct clients * next;
};

void add_new_client(struct clients* all_clients, int socket);
void add_buffer_to_socket(struct clients* all_clients,int socket, char* buffer,int read_size);
struct clients* get_client(struct clients* all_clients, int socket);
void handle_client(struct clients* client, char* root);
int main(int argc, char* argv[]) {
	struct addrinfo hints, *res;
	// create address we're going to listen on (with given port number)

	if (argc != 4)
	{
		fprintf(stderr, "ERROR: [Protocol Number], [Port Number], [Root]\n");
		exit(1);
	}
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

	memset(&hints, 0, sizeof hints);

	if (protocol == 4)
	{
		hints.ai_family = AF_INET;
	}
	else
	{
		hints.ai_family = AF_INET6;
	}
	hints.ai_family = AF_INET;       // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // for bind, listen, accept
	// node (NULL means any interface), service (port), hints, res
	int s = getaddrinfo(NULL, PORT, &hints, &res);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	// create socket
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	// reuse the socket if possible
	int const reuse = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// bind address to socket
	if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	// listen on the socket
	listen(sockfd, 5);

	// initialise an active file descriptors set
	fd_set masterfds;
	FD_ZERO(&masterfds);
	FD_SET(sockfd, &masterfds);
	// record the maximum socket number
	int maxfd = sockfd;
	struct clients* all_clients = malloc(sizeof(struct clients));
	all_clients->buffer[0] = '\0';
	all_clients->next = NULL;
	all_clients->buffer_size = 0;
	while (1) {
		// monitor file descriptors
		fd_set readfds = masterfds;
		if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) < 0) {
			perror("select");
			exit(EXIT_FAILURE);
		}

		// loop all possible descriptor
		for (int i = 0; i <= maxfd; ++i)
			// determine if the current file descriptor is active
			if (FD_ISSET(i, &readfds)) {
				// welcome socket
				// create new socket if there is new incoming connection request
				if (i == sockfd) {
					struct sockaddr_in cliaddr;
					socklen_t clilen = sizeof(cliaddr);
					int newsockfd =
						accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
					if (newsockfd < 0)
						perror("accept");
					else {
						// add the socket to the set
						add_new_client(all_clients,newsockfd);
						FD_SET(newsockfd, &masterfds);
						// update the maximum tracker
						if (newsockfd > maxfd)
							maxfd = newsockfd;
						// print out the IP and the socket number
						char ip[INET_ADDRSTRLEN];
						printf("new connection from %s on socket %d\n",
							   // convert to human readable string
							   inet_ntop(cliaddr.sin_family, &cliaddr.sin_addr,
										 ip, INET_ADDRSTRLEN),
							   newsockfd);
					}
				}
				// a message is sent from the client
				else {
					char buff[2048];
					int n = read(i, buff, 2048);
					buff[n] = '\0';
					add_buffer_to_socket(all_clients,i,buff,n);
					printf("CLIENT BUFFER:%s\n",buff);
					if (n <= 0) {
						if (n < 0)
							perror("read");
						else
							printf("socket %d close the connection\n", i);
						close(i);
						FD_CLR(i, &masterfds);
					} else
						// broadcast the message as required
						for (int j = 0; j <= maxfd; ++j)
							if (j == i && j != sockfd &&
								FD_ISSET(j, &masterfds)) {

								struct clients* client_buffer = get_client
								(all_clients,j);
								
								if(client_buffer!=NULL){
									handle_client(client_buffer,argv[3]);
								}
								perror("write");
								close(j);
								FD_CLR(j, &masterfds);
							}
					
				}
			}
	}

	return 0;
}


void add_new_client(struct clients* all_clients, int socket){

	printf("SOCKET:%d\n",socket);
	struct clients* temp = (struct clients*)malloc(sizeof(struct clients));
	temp->buffer[0] = '\0';
	temp->socket = socket;
	temp->next = all_clients;
	temp->buffer_size = 0;
	temp->next = all_clients;
	all_clients = temp;
	printf("SOCKET FIRST:%d\nNEXT IS:%d\n",all_clients->socket,all_clients->next->socket);
}	


void add_buffer_to_socket(struct clients* all_clients,int socket, char* buffer,int read_size){

	int crlf_reached = 0;
	
	for (int i = 0; strlen(buffer); i++)
	{
		if ( strlen(buffer) - i > 3 && buffer[i] == '\r' && buffer[i + 1] == '\n' && buffer[i + 2] == '\r' && buffer[i + 3] == '\n')
		{
			crlf_reached = 1;
			break;
		}

	}

	struct clients* temp;
	temp = all_clients;
	while(temp!=NULL){
		printf("SOCKET IS:%d\n",temp->socket);
		if(temp->socket == socket){
			printf("ADDED TO SOCKET_NUM:%d\n",temp->socket);
			strcat(temp->buffer,buffer);
			temp->crlf_reached = crlf_reached;
			temp->buffer_size += read_size;
			break;
		}
		temp = temp->next;
	}	

}
struct clients* get_client(struct clients* all_clients, int socket){

	struct clients* temp;
	temp = all_clients;

	while(temp!=NULL){
		if(socket == temp->socket && temp->crlf_reached){
			
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void handle_client(struct clients* client, char* root){

	char* buffer = client->buffer;
	int n = client->buffer_size;
	int newsockfd = client->socket;
	struct request *message_request = parse_request(buffer, n);

	if (!message_request->is_valid_path)
	{
		char *reply = create_bad_reply();
		write_socket(newsockfd, reply, strlen(reply));
		
	}

	int path_requested_length = strlen(message_request->fileRequested) + strlen(root) - 1;

	char full_path[path_requested_length + 1];
	strcpy(full_path, root);

	strcat(full_path, message_request->fileRequested);

	full_path[strlen(full_path)] = '\0';

	char *mime_type = get_mime_type(full_path);

	ssize_t file_size = 0;
	if (message_request->is_valid_path)
	{
		char *file_contents = read_file(full_path, &file_size);
		char *reply;
		if (file_contents == NULL)
		{
			reply = create_bad_reply();
			write_socket(newsockfd, reply, strlen(reply));
			
		}
		else
		{

			reply = create_reply(mime_type, file_contents, file_size, newsockfd);

			printf("LENGTH REPLY:%ld\n", strlen(reply));
			// n = write_socket(newsockfd, reply, file_size);
		}

		free(reply);
		free(message_request);
		free(file_contents);
	}
	
}