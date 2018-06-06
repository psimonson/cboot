#ifndef _SHELL_H_
#define _SHELL_H_

#ifndef _IO_H_
#include "io.h"
#endif
#ifndef _STRING_H_
#include "string.h"
#endif

#define MAXCMDS 3			/* max commands allowed */
#define MAXCMDLEN  64
#define MAXHELPLEN 128

typedef struct command command_t;

struct command {
	char cmd[MAXCMDLEN];
	char help[MAXHELPLEN];
	unsigned char (*func)(void);
};

/* command function prototypes */
static unsigned char cmd_sound (void);
static unsigned char cmd_help  (void);
static unsigned char cmd_exit  (void);

static command_t cmd_text[MAXCMDS] = {
	{"sound", "plays a frequency for about half second.", &cmd_sound},
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

/* cmd_sound:  play a frequency for about a half second */
static unsigned char
cmd_sound (void)
{
	char buf[64];
	unsigned short freq = 0;

	print("Enter frequency of sound (eg 100-50000): ");
	getline(buf, sizeof buf);
	print("\r\n");
	freq = (unsigned short)atoi(buf);
	if (freq < 100 || freq > 50000)
		print("Frequency was out of range.\r\n");
	else {
		print("Playing sound please wait...\r\n");
		play_sound(freq);
		timer(0x0002, 0x828b);
		stop_sound();
	}
	return 0;
}

/* cmd_help:  gives users list of available commands */
static unsigned char
cmd_help (void)
{
	list_commands(cmd_text);
	return 0;
}

/* cmd_exit:  quits the shell */
static unsigned char
cmd_exit (void)
{
	print("Exiting the shell interface...\r\n");
	return 1;
}

#endif
