/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** cserver_poll
*/

#include <sys/epoll.h>

#include "server.h"

static int (* const ifct_tab[])(cserver *server, cclient *client) = {
	_listener,
	_client,
	_stdin,
};

int cserver_poll(cserver *server, int size)
{
	cclient *p;

	for (int i = 0; i < size; ++i) {
		p = server->events[i].data.ptr;
		ifct_tab[p->use](server, p);
	}
	return (0);
}