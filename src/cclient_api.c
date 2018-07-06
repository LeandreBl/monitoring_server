/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client api
*/

#include <unistd.h>
#include <stdlib.h>

#include "server.h"

int cclient_create(cclient_t *client, int fd,
	struct sockaddr_in *saddr, enum socket_use_e use)
{
	if (scalloc(&client->cbuffer, 1, sizeof(*client->cbuffer)) == -1
		|| scalloc(&client->saddr, 1, sizeof(*client->saddr)) == -1)
		return (-1);
	if (cbuffer_create(client->cbuffer, 1 << 16) == -1) {
		trace(T_ERROR, "%s: cbuffer_create[%d] failed\n",
			__FUNCTION__, fd);
		return (-1);
	}
	*client->saddr = *saddr;
	client->fd = fd;
	client->connected = true;
	client->use = use;
	trace(T_ACK, "%s: cbuffer_create[%d] success\n", __FUNCTION__, fd);
	return (0);
}

void cclient_destroy(cclient_t *client)
{
	cbuffer_destroy(client->cbuffer);
	if (client->connected)
		close(client->fd);
	free(client->saddr);
	free(client->cbuffer);
}

void cclient_fdestroy(cclient_t *client)
{
	cclient_destroy(client);
	free(client);
}