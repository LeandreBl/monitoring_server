/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _pretty_ls
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int _pretty_ls(__attribute__ ((unused)) cserver_t *server, const char *line)
{
	char *cmd;

	if (asprintf(&cmd, "ls %s --color=tty", line) == -1)
		return (-1);
	system(cmd);
	free(cmd);
	return (0);
}