#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#include <shutils.h>

typedef struct _hello_world_process_t 
{
	const char *command;
	int (*cmd_handler)();
} hello_world_process;

static int start()
{
	
	if(f_exists("/usr/bin/hello_world"))
		exec_cmd("/usr/bin/hello_world 1>/dev/ttyS0 2>&1   &  ");
	return 0;
}

static hello_world_process hello_world_proc[] = {
		{ "boot", start },
		{ "start", start },

		{ .command = NULL }
};

int hello_world_main(int argc, char **argv)
{
	int i;

	for(i=0; hello_world_proc[i].command != NULL; i++)
	{
		if(strcmp(argv[1], hello_world_proc[i].command) == 0)	
			hello_world_proc[i].cmd_handler();
	}

	return 0;
}

int main(int argc, char **argv)
{
	return hello_world_main(argc, argv);
}

