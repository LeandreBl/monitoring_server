/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** dump_receive
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "server.h"

static int save_file(cclient_t *client, int fd, size_t size)
{
	char buffer[512];
	ssize_t rd;

	do {
		rd = (size > sizeof(buffer) ? sizeof(buffer) : size);
		rd = cbuffer_read(client->cbuffer, buffer, rd);
		write(fd, buffer, rd);
		size -= rd;
	} while (rd > 0 && size > 0);
	return (0);
}

int dump_receive(__attribute__ ((unused)) cserver_t *server, cclient_t *client)
{
	char *output;
	size_t size;
	int fd;

	if (cbuffer_getbytes(client->cbuffer, &output, ':') == -1 || output == NULL)
		return (-1);
	size = atoi(output);
	free(output);
	if (cbuffer_getbytes(client->cbuffer, &output, '\n') == -1 || output == NULL)
		return (-1);
	if (output[0] != 0)
		output[strlen(output) - 1] = 0;
	fd = open(output, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1) {
		trace(T_ERROR, "Can't open \"%s\" file: %m\n", output);
		free(output);
		return (-1);
	}
	trace(T_DEBUG, "Receiving \"%s\" (%zu bytes) file\n", output, size);
	if (save_file(client, fd, size) == -1)
		return (-1);
	trace(T_ACK, "File \"%s\" (%zu bytes) received\n", output, size);
	close(fd);
	free(output);
	return (0);
}