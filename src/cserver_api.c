/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** cserver api
*/

#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "server.h"

static int listener_stdin(cserver *server)
{
	cclient *listener;
	cclient *stdin;
	int fd;
	struct sockaddr_in saddr;

	if (scalloc(&listener, 1, sizeof(*listener)) == -1 ||
		scalloc(&stdin, 1, sizeof(*stdin)) == -1)
		return (-1);
	fd = create_server(server->port, &saddr);
	if (fd == -1) {
		trace(T_PANIC, "Fail to start server on port %u\n", server->port);
		return (-1);
	}
	listen(fd, 0);
	if (cclient_create(listener, fd, &saddr, S_LISTENER) == -1 ||
		cclient_create(stdin, 0, &saddr, S_STDIN) == -1 ||
		cserver_add_in_poll(server, listener) == -1 ||
		cserver_add_in_poll(server, stdin) == -1)
		return (-1);
	server->port = saddr.sin_port;
	return (0);
}

int cserver_create(cserver *server, uint16_t port)
{
	server->port = port;
	if (scalloc(&server->clients, 1, sizeof(*server->clients)) == -1)
		return (-1);
	if (lblgtab_create(server->clients, 5) == -1) {
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
	trace(T_INFO, "%s: started on port %u\n", __FUNCTION__, server->port);
	server->esize = 0;
	server->events = NULL;
	server->is_running = true;
	return (0);
}

int cserver_add_in_poll(cserver *server, cclient *client)
{
	struct epoll_event event;

	event.data.ptr = client;
	event.events = EPOLLIN;
	if (epoll_ctl(server->epoll, EPOLL_CTL_ADD, client->fd, &event) == -1) {
		trace(T_ERROR, "Failed to add [%d] in epoll\n", client->fd);
		return (-1);
	}
	if (server->clients->append(server->clients, client) == -1) {
		trace(T_ERROR, "Failed to append [%d] client\n", client->fd);
		return (-1);
	}
	trace(T_DEBUG, "%s: +[%d]\n", __FUNCTION__, client->fd);
	return (0);
}

int cserver_del_in_poll(cserver *server, cclient *client)
{
	if (epoll_ctl(server->epoll, EPOLL_CTL_DEL, client->fd, NULL) == -1) {
		trace(T_ERROR, "Failed to del [%d] in epoll\n", client->fd);
		return (-1);
	}
	server->clients->remove(server->clients, client, (void (*)(void *))cclient_destroy);
	trace(T_DEBUG, "%s: -[%d]\n", __FUNCTION__, client->fd);
	return (0);
}