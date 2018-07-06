/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** cserver_tpoll
*/

#include <sys/epoll.h>

#include "server.h"

static int (* const ifct_tab[])(cserver_t *server, cclient_t *client) = {
	_listener,
	_client,
};

int cserver_poll(cserver_t *server, int size)
{
	cclient_t *p;

	for (int i = 0; i < size; ++i) {
		p = server->events[i].data.ptr;
		ifct_tab[p->use](server, p);
	}
	return (0);
}

int cserver_add_in_poll(cserver_t *server, cclient_t *client)
{
	struct epoll_event event;

	event.data.ptr = client;
	event.events = EPOLLIN;
	if (epoll_ctl(server->epoll, EPOLL_CTL_ADD, client->fd, &event) == -1) {
		trace(T_ERROR, "Failed to add [%d] in epoll\n", client->fd);
		return (-1);
	}
	if (client->use != S_LISTENER && 
		gtab_append(server->clients, client) == -1) {
		trace(T_ERROR, "Failed to append [%d] client\n", client->fd);
		return (-1);
	}
	trace(T_DEBUG, "%s: +[%d]\n", __FUNCTION__, client->fd);
	return (0);
}

int cserver_del_in_poll(cserver_t *server, cclient_t *client)
{
	if (epoll_ctl(server->epoll, EPOLL_CTL_DEL, client->fd, NULL) == -1) {
		trace(T_ERROR, "Failed to del [%d] in epoll\n", client->fd);
		return (-1);
	}
	gtab_remove(server->clients, client, (void (*)(void *))cclient_destroy);
	trace(T_DEBUG, "%s: -[%d]\n", __FUNCTION__, client->fd);
	return (0);
}