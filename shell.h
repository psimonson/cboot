#ifndef _SHELL_H_
#define _SHELL_H_

#ifndef _IO_H_
#include "io.h"
#endif

#define MAXTOKS 64		/* TODO: add code to seperate into tokens */
#define MAXCMDS 2			/* max commands allowed */

typedef struct command {
	char cmd[64];
	char help[128];
	unsigned short count;
} command_t;

typedef struct cmd_tree {
	command_t command;
	struct cmd_tree *left;
	struct cmd_tree *right;
} cmd_tree_t;

#ifndef _CMD_ARRAY_OVERRIDE
static char *cmd_text[2][MAXCMDS] = {
	{"help", "displays this info.\r\n"},
	{"exit", "exits back to the main program.\r\n"}
};
#endif

/* --------------------- Functions Below ----------------------- */

static command_t
add_command (const char *name, const char *help)
{
	command_t cmd;
	strcpy ((char*)cmd.cmd, name);
	strcpy ((char*)cmd.help, help);
	++(cmd.count);
	return cmd;
}

#ifndef _CMD_TREE_OVERRIDE
static void
list_commands (cmd_tree_t *leaf)
{
	if (leaf) {
		print (leaf->command.cmd);
		list_commands (leaf->left);
		list_commands (leaf->right);
	}
}
static void
init_commands (cmd_tree_t *leaf, const char *name, const char *help)
{
	if (leaf) {
		leaf->command = add_command (name, help);
		init_commands (leaf->left, name, help);
		init_commands (leaf->right, name, help);
	}
}
#else
static void list_commands (cmd_tree_t *leaf);
static void init_commands (cmd_tree_t *leaf);
#endif

#endif
