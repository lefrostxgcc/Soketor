#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <utility.h>

static int create_client_socket(const char *address, int port);

void action_client(const char *address, int port, int num1, int num2)
{
	int		client_socket;
	int		status;
	int		result;

	client_socket = create_client_socket(address, port);
	printf("Sending request %d %d\n", num1, num2);
	send_number_pair(client_socket, num1, num2);
	printf("Getting result: ");
	result = recv_number_with_status(client_socket, &status);
	if (status == STATUS_OK)
		printf("%d\n", result);
	else
		printf("%s\n", status_message(status));
	close(client_socket);
}

static int create_client_socket(const char *address, int port)
{
	struct sockaddr_in	server_address = {};
	int					client_socket;

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);

	if (inet_pton(AF_INET, address, &server_address.sin_addr) <= 0)
	{
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}

	if (connect(client_socket, (struct sockaddr *) &server_address,
		sizeof(server_address)) < 0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}

	return client_socket;
}
