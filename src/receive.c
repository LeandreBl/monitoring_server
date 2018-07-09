/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** receive
*/

#include <string.h>

#include "server.h"

int _receive(cserver_t *server, const char *line)
{
	uint32_t addr;
	const char *filename;
	pkt_header_t header;
	cclient_t *ptr;

	addr = get_addr(line);
	filename = strchr(line, ' ');
	if (filename++ == NULL) {
		trace(T_ERROR, "/receive: Syntax error, please specify a filename\n");
		return (-1);
	}
	pkt_header(&header, strlen(filename), RECEIVE);
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr || *line == 'a')
			send_client(ptr, &header, filename);
	}
	return (0);
}