/*
** EPITECH PROJECT, 2018
** stdin
** File description:
** cobra server
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server.h"

struct parsing_s {
	const char *pattern;
	int (* link)(cserver *server, const char *line);
	const char *help;
};

static const struct parsing_s commands[] = {
	{"/exec @" , _stdin_exec, "/exec @[ip] [command]\t(execute a remote command)"},
	{"/dump @" , _stdin_dump, "/dump @[ip]\t\t(dump the oldest client answer)"},
	{"ls", _pretty_ls, NULL},
	{"/stop", _stop, "/stop\t\t\t(stops the server)"},
	{"/help", _help, "/help\t\t\t(shows this help)"},
	{"/ack", _ack, "/ack\t\t\t(shows informations about all clients)"}
};

int _help(__attribute__ ((unused)) cserver *server,
	__attribute__ ((unused)) const char *line)
{
	trace(T_INFO, "Help:\n");
	for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); ++i)
		if (commands[i].help != NULL)
			trace(T_NONE, "\t%s\n", commands[i].help);
	return (0);
}

int _stdin(cserver *server, cclient *client)
{
	char *line;
	size_t len;
	int ret;

	if (rdonly(server, client) == -1)
		return (-1);
	if (client->cbuffer->getbytes(client->cbuffer, &line, '\n') <= 1)
		return (-1);
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = 0;
	for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); ++i) {
		len = strlen(commands[i].pattern);
		if (strncasecmp(commands[i].pattern, line, len) == 0) {
			ret = commands[i].link(server, line + len);
			free(line);
			return (ret);
		}
	}
	system(line);
	free(line);
	return (0);
}