/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** client side
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

static int try_reconnect(const char *ipaddr, uint16_t port, 
	cclient *self, size_t timeout)
{
	for (size_t i = 0; i < timeout; ++i) {
		trace(T_ACK, "Try: %zu, Reconnecting ...\n", i + 1);
		self->fd = connect_to(ipaddr, port, self->saddr);
		if (self->fd != -1)
			return (0);
	}
	return (-1);
}

static int send_output(cclient *self, FILE *output)
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
	dprintf(self->fd, "%d:%s\n", exit_code, s);
	free(s);
	return (0);
}

static int run_command(cclient *self)
{
	char *cmd;
	FILE *output;

	if (self->cbuffer->getbytes(self->cbuffer, &cmd, '\n') == -1 || cmd == NULL)
		return (-1);
	if (fork() != 0)
		return (0);
	cmd[strlen(cmd) - 1] = 0;
	trace(T_INFO, "Executing: \"%s\"\n", cmd);
	output = popen(cmd, "r");
	if (output == NULL) {
		trace(T_ERROR, "Unable to exec command \"%s\"\n", cmd);
		return (1);
	}
	if (send_output(self, output) == -1)
		trace(T_ERROR, "Connection failed\n");
	exit(0);
	return (0);
}

int client_mode(const char *ipaddr, uint16_t port)
{
	cclient self;
	struct sockaddr_in saddr;
	int fd = connect_to(ipaddr, port, &saddr);
	bool is_running = true;

	if (cclient_create(&self, fd, &saddr, S_CLIENT) == -1) {
		trace(T_PANIC, "Can't start client\n");
		return (-1);
	}
	while (is_running) {
		if (self.fd == -1 && try_reconnect(ipaddr, port, &self, 5) == -1)
			break;
		rdonly(NULL, &self);
		if (run_command(&self) == -1 && try_reconnect(ipaddr, port, &self, 10) == -1)
			break;
	}
	cclient_destroy(&self);
	return (0);
}
