/*
** EPITECH PROJECT, 2018
** stdin
** File description:
** cobra server
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "server.h"
#include "colors.h"

struct parsing_s {
	const char *pattern;
	int (* link)(cserver_t *server, const char *line);
	const char *help;
};

static const struct parsing_s commands[] = {
	{"/exec @" , _stdin_exec, "/exec    @[ip] [command]\t\t(execute a remote command)"},
	{"/dump @" , _stdin_dump, "/dump    @[ip]\t\t\t\t(dump the oldest client answer)"},
	{"ls", _pretty_ls, NULL},
	{"/stop", _stop, "/stop\t\t\t\t\t(stops the server)"},
	{"/help", _help, "/help\t\t\t\t\t(shows this help)"},
	{"/ack @", _ack, "/ack     @[ip]\t\t\t\t(informations about clients)"},
	{"/eject @", _eject, "/eject   @[ip]\t\t\t\t(eject a client)"},
	{"/send @", _send, "/send    @[ip] [pathname] [filename]\t(send the file at <pathname> as <filename> to a client)"},
	{"/receive @", _receive, "/receive @[ip] [pathname] [filename]\t(receive the file at <pathname> as <filename>)"},
};

static void output_color(const char *s)
{
	const char *color = "";

	write(1, "\t", 1);
	write(1, s, 1);
	for (size_t i = 1; s[i] != 0; ++i) {
		if (s[i - 1] == '/')
			color = GREEN;
		else if (s[i - 1] == '[')
			color = CYAN;
		else if (s[i - 1] == '(')
			color = YELLOW;
		if (s[i] == '@')
			color = BOLDCYAN;
		if (s[i] == ']' || s[i] == ')' || s[i] == '[' || s[i] == '(')
			color = RESET;
		write(1, color, strlen(color));
		write(1, s + i, 1);
	}
	write(1, "\n", 1);
}

int _help(__attribute__ ((unused)) cserver_t *server,
	__attribute__ ((unused)) const char *line)
{
	trace(T_INFO, "Help (for all the commands, you can type @a instead of "
		"@[ip] to target all clients):\n");
	for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); ++i)
		if (commands[i].help != NULL)
			output_color(commands[i].help);
	return (0);
}

int _stdin(cserver_t *server, const char *line)
{
	size_t len = strlen(line);
	int ret;

	for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); ++i) {
		len = strlen(commands[i].pattern);
		if (strncasecmp(commands[i].pattern, line, len) == 0) {
			ret = commands[i].link(server, line + len);
			return (ret);
		}
	}
	system(line);
	return (0);
}