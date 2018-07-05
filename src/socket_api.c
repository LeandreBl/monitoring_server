/*
** EPITECH PROJECT, 2018
** libc
** File description:
** socket C simple API
*/

#define _GNU_SOURCE
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

uint32_t get_addr(const char *str)
{
	char dup[18] = { 0 };
	uint32_t addr;
	char *p;

	strcpy(dup, str);
	p = strchr(dup, ' ');
	if (p != NULL)
		*p = 0;
	inet_pton(AF_INET, dup, &addr);
	return (addr);
}

static int bind_and_get(int fd, struct sockaddr *server)
{
	socklen_t len = sizeof(server);

	if (bind(fd, server, sizeof(struct sockaddr_in)) == -1) {
		close(fd);
		return (-1);
	}
	if (getsockname(fd, server, &len) == -1)
		return (-1);
	return (0);
}

int create_server(uint16_t port, struct sockaddr_in *ptr)
{
	struct sockaddr_in server;

	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (-1);
	memset(&server, 0, sizeof(server));
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (bind_and_get(fd, (struct sockaddr *)&server) == -1)
		return (-1);
	if (ptr) {
		*ptr = server;
		ptr->sin_port = htons(server.sin_port);
	}
	return (fd);
}

int accept_client(int sockfd, int backlog, struct sockaddr_in *buf)
{
	socklen_t clilen;
	struct sockaddr_in client;
	int fd;

	if (listen(sockfd, backlog) == -1)
		return (-1);
	clilen = sizeof(client);
	fd = accept(sockfd, (struct sockaddr *)&client, &clilen);
	if (fd == -1)
		return (-1);
	if (buf)
		*buf = client;
	return (fd);
}

int connect_to(const char *ip, uint16_t port, struct sockaddr_in *buffer)
{
	struct hostent *info;
	struct sockaddr_in saddr;
	int fd;

	info = gethostbyname(ip);
	if (info == NULL)
		return (-1);
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (-1);
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_addr = *(struct in_addr *)info->h_addr;
	saddr.sin_port = htons(port);
	saddr.sin_family = AF_INET;
	if (connect(fd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		close(fd);
		return (-1);
	}
	if (buffer != NULL)
		*buffer = saddr;
	return (fd);
}
