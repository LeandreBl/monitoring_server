/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** client_send
*/

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

static int _send_file(cclient_t *client, int fd, const char *pathname)
{
	char buffer[512];
	ssize_t rd;

	dprintf(client->fd, "FILE_RECEIVE:%zu:%s\n", lseek(fd, 0, SEEK_END), pathname);
	lseek(fd, 0, SEEK_SET);
	do {
		rd = read(fd, buffer, sizeof(buffer));
		write(client->fd, buffer, rd);
	} while (rd > 0);
	return (0);
}

int client_send(cclient_t *client, size_t pkt_size)
{
	char *filename = calloc(pkt_size + 1, sizeof(char));
	char *pathname;
	int fd;

	if (filename == NULL) {
		dprintf(client->fd, "-1: Memory failed\n");
		return (-1);
	}
	read_wrapper(client->fd, filename, pkt_size);
	pathname = strchr(filename, ' ');
	pathname++[0] = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		dprintf(client->fd, "-1: File \"%s\" not found\n", filename);
		free(filename);
		return (-1);
	}
	_send_file(client, fd, pathname);
	free(filename);
	close(fd);
	return (0);
}