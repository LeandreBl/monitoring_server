/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client_receive
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "server.h"

int client_receive(cclient_t *client, size_t pkt_size)
{
	pkt_header_t header;
	char *filename = calloc(pkt_size + 1, sizeof(char));
	int fd;
	ssize_t rd;
	char buffer[512];

	if (filename == NULL) {
		dprintf(client->fd, "-1: calloc failed\n");
		trace(T_ERROR, "Failed to allocate memory\n");
		return (-1);
	}
	read_wrapper(client->fd, filename, pkt_size);
	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1) {
		dprintf(client->fd, "-1:Failed to open(\"%s\")\n", filename);
		trace(T_ERROR, "Failed to open(\"%s\")\n", filename);
		return (-1);
	}
	read_wrapper(client->fd, &header, sizeof(header));
	if (header.action != SEND_FILE)
		return (-1);
	do {
		rd = (header.pkt_size > sizeof(buffer)) ? sizeof(buffer) : header.pkt_size;
		rd = read_wrapper(client->fd, buffer, rd);
		if (rd == -1)
			return (-1);
		write(fd, buffer, rd);
		header.pkt_size -= rd;
	} while (header.pkt_size > 0);
	trace(T_DEBUG, "File \"%s\" (%zu bytes) received\n", filename, lseek(fd, 0, SEEK_END));
	dprintf(client->fd, "0:File \"%s\" received\n", filename);
	free(filename);
	close(fd);
	return (0);
}