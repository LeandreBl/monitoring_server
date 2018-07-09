/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** packet
*/

#include <unistd.h>

#include "server.h"

void pkt_header(pkt_header_t *header, size_t pkt_size, enum action_e action)
{
	header->magic = MAGIC;
	header->pkt_size = pkt_size;
	header->action = action;
}

ssize_t send_client(cclient_t *client, pkt_header_t *header, const void *data)
{
	ssize_t wr;
	ssize_t total;

	trace(T_DEBUG, "send: magic(%x), size(%u), action(%u)\n",
		header->magic, header->pkt_size, header->action);
	if (client->connected == false || client->use != S_CLIENT)
		return (0);
	wr = write(client->fd, header, sizeof(*header));
	if (wr != (int)sizeof(*header)) {
		trace(T_ERROR, "Failed to send header: %ld\n", wr);
		return (-1);
	}
	total = wr;
	wr = write(client->fd, data, header->pkt_size);
	if (wr != (int)header->pkt_size)
		return (-1);
	total += wr;
	return (total);
}