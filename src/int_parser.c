/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** int parser for _stdin commands
*/

#include <string.h>
#include <stdlib.h>

#include "server.h"

int int_parser(gtab_t *tab, const char *line)
{
	const char *p = strchr(line, '[');
	const char *delim = strchr(line, ']');
	long var;

	if (gtab_create(tab, 10) == -1)
		return (-1);
	while (p < delim) {
		++p;
		var = atoi(p);
		gtab_append(tab, (void *)var);
		p = strchr(p, ',');
	}
	return (0);
}
