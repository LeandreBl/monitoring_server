/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** send
*/

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "server.h"

static int _send_file(cclient_t *client, int fd, const char *filename)
{
	pkt_header_t header;
	ssize_t rd;
	char buffer[512];

	pkt_header(&header, strlen(filename), SEND);
	send_client(client, &header, filename);
	pkt_header(&header, lseek(fd, 0, SEEK_END), SEND_FILE);
	write(client->fd, &header, sizeof(header));
	lseek(fd, 0, SEEK_SET);
	do {
		rd = read(fd, buffer, sizeof(buffer));
		write(client->fd, buffer, rd);
	} while (rd > 0);
	return (0);
}

int _send(cserver_t *server, const char *line)
{
	char **parse = wordtab(line, " ");
	uint32_t addr;
	cclient_t *ptr;
	int fd;

	if (parse == NULL || tablen(parse) < 3) {
		trace(T_ERROR, "/send: Syntax error\n");
		return (-1);
	}
	addr = get_addr(parse[0]);
	trace(T_DEBUG, "path: %s, file: %s\n", parse[1], parse[2]);
	fd = open(parse[1], O_RDONLY);
	if (fd == -1) {
		trace(T_ERROR, "Can't open \"%s\" file\n", parse[1]);
		return (-1);
	}
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr || parse[0][0] == 'a')
			_send_file(ptr, fd, parse[2]);
	}
	close(fd);
	free_tab(parse);
	return (0);
}