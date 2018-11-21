#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum { APP_SERVER, APP_CLIENT };

struct socketor_args
{
	const char *address;
	int app;
	int port;
	int operation;
	int num1;
	int num2;
};

static const char *usage_message =
	"Usage: socketor server port operation\n"
	"Usage: socketor client address port num1 num2\n";

static int parse_cmd(int argc, char *argv[], struct socketor_args *args);
static int parse_server_cmd(int argc, char *argv[], struct socketor_args *args);
static int parse_client_cmd(int argc, char *argv[], struct socketor_args *args);
static void fail(const char *message);
static void action_server(int port, int operation);
static void action_client(const char *address, int port, int num1, int num2);
static int check_operation(int operation);

int main(int argc, char *argv[]) 
{
	struct socketor_args	args;

	if (parse_cmd(argc, argv, &args) < 0)
		fail(usage_message);

	switch (args.app)
	{
		case APP_SERVER:
			action_server(args.port, args.operation);
			break;
		case APP_CLIENT:
			action_client(args.address, args.port, args.num1, args.num2);
			break;
	}

	return 0;
}

static int parse_cmd(int argc, char *argv[], struct socketor_args *args)
{
	if (argc < 2 || argc > 5)
		return -1;

	if (argc > 1)
	{
		if (!strcmp(argv[1], "server"))
			return parse_server_cmd(argc, argv, args);
		else if (!strcmp(argv[1], "client"))
			return parse_client_cmd(argc, argv, args);
		else
			return -1;
	}
}

static void fail(const char *message)
{
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}

static int parse_server_cmd(int argc, char *argv[], struct socketor_args *args)
{
	if (argc > 2)
		args->port = atoi(argv[2]);
	else
		return -1;

	if (argc > 3)
		args->operation = argv[3][0];
	else
		return -1;

	if (argv[3][1] != '\0' || check_operation(args->operation) < 0)
		return -1;

	args->app = APP_SERVER;
	
	return 0;
}

static int parse_client_cmd(int argc, char *argv[], struct socketor_args *args)
{
	args->app = APP_CLIENT;
	return 0;
}

static int check_operation(int operation)
{
	switch (operation)
	{
		case '+': case '-' : case '*' : case '/' : case '%':
			return 0;
	}
	return -1;
}

static void action_server(int port, int operation)
{
}

static void action_client(const char *address, int port, int num1, int num2)
{
}
