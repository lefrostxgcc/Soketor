#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

int		rand_number(int min, int max)
{
	srand(time(0));
	return rand() % (max - min) + min;
}

void	send_number(int socket, int number)
{
	char		buf[32];
	int			out_msg_len;

	out_msg_len = snprintf(buf, sizeof(buf)/sizeof(buf[0]), "%d\n", number);
	if (write(socket, buf, out_msg_len) < 0)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

int	recv_number(int socket)
{
	char		buf[32];
	int			bytes_read;
	int			number;

	bytes_read = read(socket, buf, sizeof(buf) / sizeof(buf[0]) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[bytes_read] = '\0';
	sscanf(buf, "%d", &number);
	return number;
}

void send_number_pair(int socket, int num1, int num2)
{
	char		buf[32];
	int			out_msg_len;

	out_msg_len = snprintf(buf, sizeof(buf)/sizeof(buf[0]), "%d %d\n",
		num1, num2);
	if (write(socket, buf, out_msg_len) < 0)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

void recv_number_pair(int socket, int *num1, int *num2)
{
	char		buf[32];
	int			bytes_read;
	int			number;

	bytes_read = read(socket, buf, sizeof(buf) / sizeof(buf[0]) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[bytes_read] = '\0';
	sscanf(buf, "%d %d", num1, num2);
}

void send_number_with_status(int socket, int number, int status)
{
	char		buf[32];
	int			out_msg_len;

	out_msg_len = snprintf(buf, sizeof(buf)/sizeof(buf[0]), "%d %d\n",
		number, status);
	if (write(socket, buf, out_msg_len) < 0)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

int	recv_number_with_status(int socket, int *status)
{
	char		buf[32];
	int			bytes_read;
	int			number;

	bytes_read = read(socket, buf, sizeof(buf) / sizeof(buf[0]) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[bytes_read] = '\0';
	sscanf(buf, "%d %d", &number, status);
	return number;
}

const char *status_message(int status)
{
	static const char *messages[] =
	{
		"ok",
		"error: division by zero"
	};
	if (status < 0 || status >= sizeof(messages) / sizeof(messages[0]))
		return "";
	else
		return messages[status];
}
