/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stop
*/

#include "server.h"

int _stop(cserver_t *server, __attribute__ ((unused)) const char *line)
{
	server->is_running = false;
	return (0);
}