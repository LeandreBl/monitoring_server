/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client_eject
*/

#include <stdlib.h>

#include "server.h"

int client_eject(__attribute__ ((unused)) cclient_t *client,
	__attribute__ ((unused)) size_t pkt_size)
{
	trace(T_INFO, "Ejected by server\n");
	exit(0);
	return (0);
}