/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** _stop
*/

#include "server.h"

int _stop(cserver *server, __attribute__ ((unused)) const char *line)
{
	trace(T_INFO, "Stopping server ...\n");
	server->is_running = false;
	return (0);
}