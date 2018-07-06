/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

static int server_mode(uint16_t port)
{
	cserver_t server;

	if (cserver_create(&server, port) == -1)
		return (-1);
	cserver_run(&server);
	cserver_destroy(&server);
	return (0);
}

static void usage(const char *av0)
{
	printf("USAGE: %s [MODE] [PORT]\n"
	"\t%s --server [port]\n"
	"\t%s --client [ip] [port]\n", av0, av0, av0);
}

int main(int ac, char **av)
{
	if (ac == 3 && strcmp(av[1], "--server") == 0)
			return (server_mode(atoi(av[2])));
	else if (ac == 4 && strcmp(av[1], "--client") == 0)
			return (client_mode(av[2], atoi(av[3])));
	else
			usage(av[0]);
	return (0);
}
