/*
** EPITECH PROJECT, 2018
** cobra_server
** File description:
** _stind_help
*/

#include "server.h"
#include "colors.h"

int _help(__attribute__ ((unused)) cserver_t *server,
	__attribute__ ((unused)) const char *line)
{
	trace(T_INFO, "Help (for all the commands, you can type @a instead of "
		"@[ip] to target all clients:\n");
	for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); ++i)
		if (commands[i].help != NULL) {
			trace(T_NONE, "\t");
			for (size_t j = 0; commands[i].help[j] != 0; ++j) {
				output_color(commands[i].help[j]);
				trace(T_NONE, "%c", commands[i].help[j]);
			}
			trace(T_NONE, "\n");
		}
	return (0);
}
