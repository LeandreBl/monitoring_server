/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** rdonly
*/

#include <unistd.h>

#include "server.h"

static void rdonly_del(cserver_t *server, cclient_t *client)
{
	if (client->fd == 0)
		server->is_running = false;
	trace(T_INFO, "Client {%d} disconnected.\n",
		client->fd);
	cserver_del_in_poll(server, client);
}

int rdonly(cserver_t *server, cclient_t *client)
{
	char buffer[512] = { 0 };
	ssize_t rd;
	ssize_t lsize;

	do {
		lsize = cbuffer_lsize(client->cbuffer);
		if (lsize == 0)
			return (0);
		if (lsize > (ssize_t)sizeof(buffer))
		lsize = (ssize_t)sizeof(buffer);
		rd = read(client->fd, buffer, sizeof(buffer));
		if (rd <= 0) {
			if (server != NULL)
				rdonly_del(server, client);
			return (rd);
		}
		cbuffer_write(client->cbuffer, buffer, rd);
	} while (rd == lsize);
	return (0);
}
