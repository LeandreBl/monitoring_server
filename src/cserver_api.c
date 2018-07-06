/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** cserver_t api
*/

#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "server.h"

static int listener_stdin(cserver_t *server)
{
	int fd;
	struct sockaddr_in saddr;

	if (scalloc(&server->listener, 1, sizeof(*server->listener)) == -1 ||
		scalloc(&server->stdin, 1, sizeof(*server->stdin)) == -1)
		return (-1);
	fd = create_server(server->port, 50, &saddr);
	if (fd == -1) {
		trace(T_PANIC, "Fail to start server on port %u\n", server->port);
		return (-1);
	}
	listen(fd, 0);
	if (cclient_create(server->listener, fd, &saddr, S_LISTENER) == -1 ||
		cserver_add_in_poll(server, server->listener) == -1)
	server->port = saddr.sin_port;
	return (0);
}

int cserver_create(cserver_t *server, uint16_t port)
{
	server->port = port;
	if (scalloc(&server->clients, 1, sizeof(*server->clients)) == -1)
		return (-1);
	if (gtab_create(server->clients, 5) == -1) {
		trace(T_PANIC, "lblgtab_create failed\n");
		return (-1);
	}
	server->epoll = epoll_create1(0);
	if (server->epoll == -1) {
		trace(T_PANIC, "Failed to create epoll\n");
		return (-1);
	}
	if (listener_stdin(server) == -1)
		return (-1);
	server->esize = 0;
	server->events = NULL;
	server->is_running = true;
	if (pthread_create(server->stdin, NULL, stdin_thread, server) == -1)
		return (-1);
	trace(T_INFO, "%s: started on port %u\n", __FUNCTION__, server->port);
	return (0);
}

void cserver_destroy(cserver_t *server)
{
	gtab_destroy(server->clients, (void (*)(void *))cclient_fdestroy);
	cclient_destroy(server->listener);
	pthread_join(*server->stdin, NULL);
	free(server->listener);
	free(server->stdin);
	free(server->clients);	
	free(server->events);
	trace(T_ACK, "\nStopping server[...]\n");
}