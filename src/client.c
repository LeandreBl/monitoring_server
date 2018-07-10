/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _client
*/

#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "server.h"

static const client_output_parser_t ptab[] = {
	{ "EXECUTE", dump_execute },
	{ "RECEIVE", dump_receive },
	{ "ACK", dump_ack },
};

int _client(cserver_t *server, cclient_t *client)
{
	char *pattern;

	if (rdonly(server, client) == -1)
		return (-1);
	if (cbuffer_getbytes(client->cbuffer, &pattern, ':') == -1)
		return (-1);
	if (pattern == NULL || strlen(pattern) == 0) {
		free(pattern);
		return (-1);
	}
	for (size_t i = 0; i < sizeof(ptab) / sizeof(*ptab); ++i) {
		if (strncmp(pattern, ptab[i].pattern, strlen(ptab[i].pattern)) == 0) {
			free(pattern);
			return (ptab[i].link(server, client));
		}
	}
	free(pattern);
	return (0);
}
