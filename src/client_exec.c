/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client_exec
*/

#include <stdlib.h>

#include "server.h"

int client_exec(cclient_t *client, size_t pkt_size)
{
	char *command = calloc(pkt_size + 1, sizeof(char));
	FILE *output;

	if (command == NULL || read_wrapper(client->fd, command, pkt_size) <= 0) {
		trace(T_ERROR, "Failed to execute \"%s\"\n", command);
		return (-1);
	}
	trace(T_DEBUG, "executing: \"%s\"\n", command);
	output = popen(command, "r");
	if (output == NULL) {
		trace(T_ERROR, "Unable to popen \"%s\"\n", command);
		return (-1);
	}
	if (client_send_output(client, output) == -1)
		trace(T_ERROR, "Connection failed\n");
	free(command);
	return (0);
}