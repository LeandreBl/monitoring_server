/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stdin_dump
*/

#include <stdlib.h>

#include "server.h"

static int _dump(cclient_t *client)
{
	char *dump;
	char *see;
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr;

	if (client->use != S_CLIENT)
		return (0);
	if (cbuffer_getbytes(client->cbuffer, &dump, '\0') == -1)
		return (-1);
	if (dump == NULL)
		see = "(null)\n";
	else
		see = dump;
	trace(T_DUMP, "\t%u.%u.%u.%u:\n%s----------------------------\n",
		p[0], p[1], p[2], p[3], see);
	free(dump);
	return (0);
}

int _stdin_dump(cserver_t *server, const char *line)
{
	uint32_t addr;
	cclient_t *ptr;

	addr = get_addr(line);
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr || *line == 'a')
			return (_dump(ptr));
	}
	trace(T_ERROR, "/dump incorrect ip: %s\n", line);
	return (0);
}
