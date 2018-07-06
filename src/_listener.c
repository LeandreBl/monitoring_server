/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _listener
*/

#include "server.h"

int _listener(cserver_t *server, cclient_t *client)
{
	cclient_t *new;
	uint8_t *p;
	struct sockaddr_in saddr;
	int fd;

	fd = accept_client(client->fd, &saddr);
	if (fd == -1) {
		trace(T_ERROR, "Failed to accept new client: %m\n");
		return (-1);
	}
	if (scalloc(&new, 1, sizeof(*new)) == -1 ||
		cclient_create(new, fd, &saddr, S_CLIENT) == -1 ||
		cserver_add_in_poll(server, new) == -1)
		return (-1);
	p = (uint8_t *)&new->saddr->sin_addr;
	trace(T_INFO, "New client: %u.%u.%u.%u : %u added\n",
		p[0], p[1], p[2], p[3], new->saddr->sin_port);
	return (0);
}
