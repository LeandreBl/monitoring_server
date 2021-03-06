/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _ack
*/

#include "server.h"

static void _ack_cli(cclient_t *client)
{
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr;

	trace(T_ACK, "[%u.%u.%u.%u:%u]     \tfd: %d\tunused bytes: %zu\n",
	p[0], p[1], p[2], p[3], client->saddr->sin_port, client->fd,
	client->cbuffer->size - cbuffer_lsize(client->cbuffer));
}

int _ack(cserver_t *server, __attribute__ ((unused)) const char *line)
{
	cclient_t *p;

	if (server->clients->len <= 1) {
		trace(T_ERROR, "No client connected\n");
		return (1);
	}
	trace(T_INFO, "%zu client connected:\n", server->clients->len - 1);
	for (size_t i = 0; i < server->clients->len; ++i) {
		p = server->clients->i[i];
		if (p->use == S_CLIENT)
			_ack_cli(p);
	}
	return (0);
}
