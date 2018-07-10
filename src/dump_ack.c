/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** dump_ack
*/

#include <stdlib.h>

#include "server.h"
#include "colors.h"

int dump_ack(__attribute__ ((unused)) cserver_t *server, cclient_t *client)
{
	const char *color;
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr.s_addr;
	char *output;
	int code;

	if (cbuffer_getbytes(client->cbuffer, &output, ':') == -1 || output == NULL)
		return (-1);
	code = atoi(output);
	if (code == 0)
		color = BOLDGREEN;
	else
		color = BOLDRED;
	free(output);
	if (cbuffer_getbytes(client->cbuffer, &output, '\n') == -1 || output == NULL)
		return (-1);
	trace(T_DUMP, "[%s%d%s] %u.%u.%u.%u: %s", color, code, RESET,
		 p[0], p[1], p[2], p[3], output);
	free(output);
	return (0);
}