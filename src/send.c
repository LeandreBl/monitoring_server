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
static int get_name(const char *line, char **p)
{
	line = strchr(line, ' ');
	if (line++ == NULL) {
		trace(T_ERROR, "/send: syntax error\n");
		return (-1);
	}
	*p = strndup(line, strcspn(line, " \t"));
	if (*p == NULL)
		return (-1);
	return (0);
}

int _send(cserver_t *server, const char *line)
{
	uint32_t addr;
	char *pathname;
	char *filename;
	cclient_t *ptr;
	bool a = (*line == 'a');
	int fd;

	addr = get_addr(line);
	if (get_name(line, &pathname) == -1)
		return (-1);
	line = strchr(line, ' ');
	if (line == NULL) {
		trace(T_ERROR, "/send: no filename\n");
		return (-1);
	}
	if (get_name(line + 1, &filename) == -1)
		return (-1);
	trace(T_DEBUG, "path: %s, file: %s\n", pathname, filename);
	fd = open(pathname, O_RDONLY);
	free(pathname);
	if (fd == -1) {
		trace(T_ERROR, "Can't open \"%s\" file\n", pathname);
		return (-1);
	}
	for (size_t i = 1; i < server->clients->len; ++i) {
		ptr = server->clients->i[i];
		if (ptr->saddr->sin_addr.s_addr == addr || a == true)
			_send_file(ptr, fd, filename);
	}
	close(fd);
	free(filename);
	return (0);
}