#ifndef CHIP_GUESS_COMMON_H
#define CHIP_GUESS_COMMON_H

enum {MIN_NUMBER = 1, MAX_NUMBER = 100};
enum {NUMBER_ERROR, NUMBER_EQUAL, NUMBER_LESS, NUMBER_GREATER};

enum { STATUS_OK, STATUS_DIVISION_BY_ZERO, STATUS_UNKNOWN_OPERATION };

int		rand_number(int min, int max);
void	send_number(int socket, int number);
void	send_number_with_status(int socket, int number, int status);
void	send_number_pair(int socket, int num1, int num2);
int		recv_number(int socket);
int		recv_number_with_status(int socket, int *status);
void	recv_number_pair(int socket, int *num1, int *num2);
void	action_server(int port, int operation);
void	action_client(const char *address, int port, int num1, int num2);
const char *status_message(int status);

#endif
