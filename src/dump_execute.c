/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** dump_execute
*/

#include <stdlib.h>

#include "server.h"
#include "colors.h"

int dump_execute(__attribute__ ((unused)) cserver_t *server, cclient_t *client)
{
	const char *color;
	char *output;
	int code;
	size_t len;
	uint8_t *p = (uint8_t *)&client->saddr->sin_addr.s_addr;

	if (cbuffer_getbytes(client->cbuffer, &output, ':') == -1
		|| output == NULL)
		return (-1);
	code = atoi(output);
	if (code == 0)
		color = BOLDGREEN;
	else
		color = BOLDRED;
	free(output);
	if (cbuffer_getbytes(client->cbuffer, &output, ':') == -1
		|| output == NULL)
		return (-1);
	len = atoi(output);
	free(output);
	output = calloc(len + 1, sizeof(char));
	if (cbuffer_read(client->cbuffer, output, len) < len) {
		trace(T_ERROR, "Can't dump %u.%u.%u.%u output\n", p[0], p[1], p[2], p[3]);
		return (-1);
	}
	trace(T_DUMP, "[%s%d%s] %u.%u.%u.%u\n%s", color, code, RESET, p[0],
		p[1], p[2], p[3], output);
	free(output);
	return (0);
}