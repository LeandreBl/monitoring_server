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
	const char *filenames;
	pkt_header_t header;
	cclient_t *ptr;

	addr = get_addr(line);
	filenames = strchr(line, ' ');
	if (filenames == NULL || strchr(filenames + 1, ' ') == NULL) {
		trace(T_ERROR, "/receive: Syntax error, please specify a filename\n");
		return (-1);
	}
	pkt_header(&header, strlen(filenames + 1), RECEIVE);
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr || *line == 'a')
			send_client(ptr, &header, filenames + 1);
	}
	return (0);
}