/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** run
*/

#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>

#include "server.h"

static int cserver_tresize_events(cserver_t *server)
{
	if (server->esize != server->clients->len) {
		server->events = realloc(server->events,
			 sizeof(*server->events) * server->clients->len);
		if (server->events == NULL) {
			trace(T_ERROR, "Failed to realloc event list\n");
			return (-1);
		}
		server->esize = server->clients->len;
	}
	return (0);
}

int cserver_run(cserver_t *server)
{
	int size = 0;

	while (server->is_running) {
		if (cserver_tresize_events(server) == -1)
			return (-1);
		if (server->events != NULL) {
			size = epoll_wait(server->epoll, server->events, server->clients->len,
				10 * (server->clients->len + 1));
			if (size == -1 && errno != EINTR) {
				trace(T_ERROR, "epoll_wait failed: %m\n");
				return (-1);
			}
		if (cserver_poll(server, size) == -1)
			return (-1);
		}
	}
	return (0);
}
