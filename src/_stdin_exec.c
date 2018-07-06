/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stdin_exec
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "server.h"

static int _exec(cclient_t *client, const char *cmd)
{
	if (client->connected && client->use == S_CLIENT)
		return (dprintf(client->fd, "%s\n", cmd));
	return (0);
}

int _stdin_exec(cserver_t *server, const char *line)
{
	const char *cmd = strchr(line, ' ');
	uint32_t addr;
	uint8_t *p;
	cclient_t *ptr;

	if (cmd == NULL) {
		trace(T_ERROR, "usage: /exec @[ip] [command]\n\t\t"
			"if @a is used, the command is send to all clients\n");
		return (-1);
	}
	++cmd;
	if (line[0] == 'a') {
		trace(T_INFO, "Sending \"%s\" to %u clients\n", cmd, server->clients->len - 1);
		for (size_t i = 0; i < server->clients->len; ++i)
			_exec(server->clients->i[i], cmd);
		return (0);
	}
	addr = get_addr(line);
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		p = (uint8_t *)&ptr->saddr->sin_addr;
		if (ptr->saddr->sin_addr.s_addr == addr) {
			trace(T_INFO, "Sending \"%s\" to %u.%u.%u.%u\n",
			cmd, p[0], p[1], p[2], p[3]);
			return (_exec(server->clients->i[i], cmd));
		}
	}
	trace(T_ERROR, "/exec, incorrect ip\n");
	return (-1);
}
