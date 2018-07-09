/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client_send_output
*/

#include <stdlib.h>

#include "server.h"

int client_send_output(cclient_t *self, FILE *output)
{
	char *s = NULL;
	int exit_code;
	size_t len = 0;
	size_t rd;

	do {
		s = realloc(s, len + 513);
		if (s == NULL) {
			dprintf(self->fd, "-1: Not enough memory\n");
			return (-1);
		}
		rd = fread(s + len, 1, 512, output);
		len += rd;
	} while (rd == 512);
	if (len > 0 && s[len - 1] == '\n')
		--len;
	s[len] = 0;
	exit_code = pclose(output) / 256;
	s = realloc(s, len + 1);
	if (s == NULL)
		dprintf(self->fd, "%d:<!>Realloc failed<!>\n", exit_code);
	else
		dprintf(self->fd, "%d:%s\n", exit_code, s);
	free(s);
	return (0);
}