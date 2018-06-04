#ifndef _SHELL_H_
#define _SHELL_H_

#ifndef _IO_H_
#include "io.h"
#endif

#define MAXCMDS 2			/* max commands allowed */
#define MAXCMDLEN  64
#define MAXHELPLEN 128

typedef struct command command_t;

struct command {
	char cmd[MAXCMDLEN];
	char help[MAXHELPLEN];
	unsigned char (*func)(void);
};

/* command function prototypes */
static unsigned char cmd_help (void);
static unsigned char cmd_exit (void);

static command_t cmd_text[MAXCMDS] = {
	{"help", "displays this info.", &cmd_help},
	{"exit", "exits back to the main program.", &cmd_exit}
};

/* --------------------- Functions Below ----------------------- */

static command_t
add_command (const char *name, const char *help)
{
	command_t cmd;
	strcpy (cmd.cmd, name);
	strcpy (cmd.help, help);
	return cmd;
}

static void
list_commands (command_t cmds[])
{
	int i;
	for (i = 0; i < MAXCMDS; i++) {
		print (cmds[i].cmd);
		print (" - ");
		print (cmds[i].help);
		print ("\r\n");
	}
}

static unsigned char
compare_commands (command_t cmds[], const char *input)
{
	unsigned char i;
	for (i = 0; i < MAXCMDS; i++)
		if (!strcmp(cmds[i].cmd, input))
			return i;
	return -1;
}

/* ----------------------- Command Functions ---------------------- */

static unsigned char
cmd_help (void)
{
	list_commands(cmd_text);
	return 0;
}

static unsigned char
cmd_exit (void)
{
	print("Exiting the shell interface...\r\n");
	return 1;
}

#endif
