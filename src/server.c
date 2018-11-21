#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utility.h"

static int create_server_socket(int port, int backlog);
static void accept_clients(int server_socket, int operation);
static void process_client(int client_socket, int operation);
static int perform_calculation(int num1, int num2, int operation);

void action_server(int port, int operation)
{
	int		server_socket;

	server_socket = create_server_socket(port, 10);
	printf(">>Started server with %c operation on %d port\n",
		operation, port);
	accept_clients(server_socket, operation);
	close(server_socket);
}

static int create_server_socket(int port, int backlog)
{
	struct sockaddr_in	channel;
	int					server_socket;
	int					opt;

	opt = 1;
	channel.sin_family = AF_INET;
	channel.sin_addr.s_addr = htonl(INADDR_ANY);
	channel.sin_port = htons(port);

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
					&opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	if (bind(server_socket, (struct sockaddr *) &channel, sizeof(channel)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_socket, backlog) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	return server_socket;
}

static void accept_clients(int server_socket, int operation)
{
	int			client_socket;

	while (1)
	{
		client_socket = accept(server_socket, 0, 0);
		if (client_socket < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		process_client(client_socket, operation);
		close(client_socket);
	}
}

static void process_client(int client_socket, int operation)
{
	int		num1;
	int		num2;
	int		result;

	recv_number_pair(client_socket, &num1, &num2);
	result = perform_calculation(num1, num2, operation);
	printf(">>Accepted client: %d %c %d = %d\n",
		num1, operation, num2, result);
	send_number(client_socket, result);
}

static int perform_calculation(int num1, int num2, int operation)
{
	switch (operation)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			if (num2 == 0)
				break;
			return num1 / num2;
		case '%':
			if (num2 == 0)
				break;
			return num1 % num2;
	}
	return INT_MAX;
}
