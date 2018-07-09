/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client side
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "server.h"

static int try_reconnect(const char *ipaddr, uint16_t port, 
	cclient_t *self, size_t timeout)
{
	for (size_t i = 0; i < timeout; ++i) {
		trace(T_ACK, "Try: %zu, Reconnecting ...\n", i + 1);
		self->fd = connect_to(ipaddr, port, self->saddr);
		if (self->fd != -1) {
			trace(T_INFO, "Reconnected!\n");
			return (0);
		}
		sleep(1);
	}
	return (-1);
}

static const client_parser_t acts[] = {
	{ COMMAND, client_exec },
	{ EJECT, client_eject },
	{ SEND, client_receive },
	{ RECEIVE, client_send },
};

int client_mode(const char *ipaddr, uint16_t port)
{
	cclient_t self;
	struct sockaddr_in saddr;
	int fd = connect_to(ipaddr, port, &saddr);
	pkt_header_t header;

	if (cclient_create(&self, fd, &saddr, S_CLIENT) == -1) {
		trace(T_PANIC, "Can't start client\n");
		return (-1);
	}
	if (fd != -1)
		trace(T_INFO, "Connected !\n");
	while (true) {
		if (self.fd == -1 && try_reconnect(ipaddr, port, &self, 60) == -1)
			break;
		if (read_wrapper(self.fd, &header, sizeof(header)) == sizeof(header)) {
			trace(T_DEBUG, "magic(%x), size(%u), action(%d)\n", header.magic,
				header.pkt_size, header.action);
			if (header.magic != MAGIC) {
				trace(T_ERROR, "Wrong magic: %x\n", header.magic);
				return (-1);
			}
			for (size_t i = 0; i < sizeof(acts) / sizeof(*acts); ++i)
				if (acts[i].action == header.action)
					acts[i].link(&self, header.pkt_size);
		}
		else
			try_reconnect(ipaddr, port, &self, 10);
	}
	cclient_destroy(&self);
	return (0);
}
