/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** eject
*/

#include <stdio.h>

#include "server.h"

static int send_eject(cclient_t *client)
{
	pkt_header_t header;

	pkt_header(&header, 0, EJECT);
	if (client_send(client, &header, NULL) == -1)
		return (-1);
	return (0);
}

int _eject(cserver_t *server, const char *line)
{
	uint32_t addr;
	cclient_t *ptr;
	uint8_t *p = (uint8_t *)&addr;

	if (server->clients->len <= 1) {
		trace(T_ERROR, "No client connected\n");
		return (0);
	}
	addr = get_addr(line);
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (*line == 'a' || addr == ptr->saddr->sin_addr.s_addr) {
			send_eject(ptr);
			cserver_del_in_poll(server, ptr);
			trace(T_INFO, "Ejecting %u.%u.%u.%u\n", p[0], p[1], p[2], p[3]);
		}
	}
	return (0);
}