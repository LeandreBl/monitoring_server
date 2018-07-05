/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stdin_dump
*/

#include "server.h"

static int _dump(cclient *client)
{
	char *dump;
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr;

	if (client->use != S_CLIENT)
		return (0);
	if (client->cbuffer->getbytes(client->cbuffer, &dump, '\0') == -1)
		return (-1);
	if (dump == NULL)
		dump = "(null)\n";
	trace(T_DUMP, "\t%u.%u.%u.%u:\n%s----------------------------\n",
		p[0], p[1], p[2], p[3], dump);
	return (0);
}

int _stdin_dump(cserver *server, const char *line)
{
	uint32_t addr;
	cclient *ptr;

	if (line[0] == 'a') {
		for (size_t i = 0; i < server->clients->len; ++i)
			_dump(server->clients->i[i]);
		return (0);
	}
	addr = get_addr(line);
	for (size_t i = 0; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr)
			return (_dump(ptr));
	}
	trace(T_ERROR, "/dump incorrect ip: %s\n", line);
	return (0);
}
