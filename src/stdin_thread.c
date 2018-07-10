/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** stdin_thread
*/

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include "server.h"
#include "colors.h"

void *stdin_thread(void *p)
{
	cserver_t *server = p;
	char *line = NULL;

	while (server->is_running) {
		line = readline(BOLDYELLOW "-> " RESET);
		if (line == NULL)
			server->is_running = false;
		else {
			epur_str(line);
			_stdin(server, line);
			add_history(line);
			free(line);
		}
	}
	clear_history();
	return (NULL);
}
