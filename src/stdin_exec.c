/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stdin_exec
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

static int _exec(cclient_t *client, const char *cmd)
{
	pkt_header_t header;

	pkt_header(&header, strlen(cmd), COMMAND);
	if (client->connected && client->use == S_CLIENT)
		return (send_client(client, &header, cmd));
	return (0);
}

static int _error(cserver_t *server, const char *command)
{
	if (command == NULL) {
		trace(T_ERROR, "usage: /exec @[ip] [command]\n\t\t"
			"if @a is used, the command is send to all clients\n");
		return (-1);
	}
	if (server->clients->len <= 1) {
		trace(T_ERROR, "No client connected\n");
		return (-1);
	}
	return (0);
}

static bool _exec_loop(cserver_t *server, const char *command, uint32_t addr, bool all)
{
	cclient_t *ptr;
	uint8_t *p;
	bool done = false;

	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		p = (uint8_t *)&ptr->saddr->sin_addr;
		if (ptr->saddr->sin_addr.s_addr == addr || all == true) {
			if (all == false)
				trace(T_INFO, "Sending \"%s\" to %u.%u.%u.%u\n",
					command, p[0], p[1], p[2], p[3]);
			_exec(server->clients->i[i], command);
			done = true;
		}
	}
	return (done);
}

int _stdin_exec(cserver_t *server, const char *line)
{
	const char *command = strchr(line, ' ');
	uint32_t addr;

	if (_error(server, command) == -1)
		return (-1);
	addr = get_addr(line);
	if (*line == 'a')
		trace(T_INFO, "Sending \"%s\" to %u clients\n", command + 1, server->clients->len - 1);
	if (_exec_loop(server, command + 1, addr, *line == 'a') == false)
		trace(T_ERROR, "/exec, incorrect ip\n");
	return (-1);
}