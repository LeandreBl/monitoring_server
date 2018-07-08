/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _client
*/

#include <stdlib.h>

#include "colors.h"
#include "server.h"

int _client(cserver_t *server, cclient_t *client)
{
	char *line;
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr;
	const char *color;
	int code;

	if (rdonly(server, client) == -1)
		return (-1);
	if (cbuffer_getbytes(client->cbuffer, &line, ':') == -1)
		return (-1);
	if (line == NULL)
		return (-1);
	code = atoi(line);
	if (code == 0)
		color = BOLDGREEN;
	else
		color = BOLDRED;
	free(line);
	trace(T_INFO, "%u.%u.%u.%u: [%s%d%s]\n", p[0], p[1], p[2], p[3], color, code, RESET);
	return (0);
}
