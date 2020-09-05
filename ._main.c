/*---------------------------------------------------------------------------*/
/*                                                                           */
/* WARN: Please don't modify this default file!!!                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <tinyara/config.h>
#include <stdio.h>
#include <unistd.h>
#ifdef CONFIG_TASH
#include <shell/tash.h>
#endif

#ifndef APP_PRIORITY
#define APP_PRIORITY 100
#endif

#ifndef APP_STACKSIZE
#define APP_STACKSIZE 2048
#endif

extern int demo_main(int argc, char *argv[]);

static int main(int argc, char *argv[])
{
#ifdef CONFIG_TASH
	/* add tash command */
	tash_cmd_install("demo", demo_main, TASH_EXECMD_SYNC);
#endif

	demo_main(argc, argv);

	return 0;
}

int _main(int argc, char *argv[])
{
	int pid;

	/*
	 * Create Task For async job
	 */
	pid = task_create("demo", APP_PRIORITY, APP_STACKSIZE, main, argv);
	if (pid < 0) {
		/*
		 * Error : Can't Create task
		 */
		printf("demo is not started, err = %d\n", pid);
	}

	return 0;
}

