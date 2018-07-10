/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client_send_output
*/

#include <stdlib.h>
#include <string.h>

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
			dprintf(self->fd, "ACK:-1:/exec: Not enough memory\n");
			return (-1);
		}
		rd = fread(s + len, 1, 512, output);
		len += rd;
	} while (rd == 512);
	if (len > 0 && s[len - 1] == '\n')
		--len;
	s[len] = 0;
	exit_code = pclose(output) / 256;
	if (s == NULL)
		dprintf(self->fd, "ACK:%d:/exec: Realloc failed\n", exit_code);
	else
		dprintf(self->fd, "EXECUTE:%d:%zu:%s\n", exit_code, strlen(s) + 1, s);
	free(s);
	return (0);
}