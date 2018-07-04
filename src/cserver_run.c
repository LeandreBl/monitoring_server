/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** run
*/

#include <stdlib.h>
#include <sys/epoll.h>

#include "server.h"

static int cserver_resize_events(cserver *server)
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

int cserver_run(cserver *server)
{
	int size = 0;

	while (server->is_running) {
		if (cserver_resize_events(server) == -1)
			return (-1);
		if (server->events != NULL) {
			size = epoll_wait(server->epoll, server->events, server->clients->len,
				10 * (server->clients->len + 1));
			if (size == -1) {
				trace(T_ERROR, "epoll_wait failed: %m\n");
				return (-1);
			}
		if (cserver_poll(server, size) == -1)
			return (-1);
		}
	}
	return (0);
}
