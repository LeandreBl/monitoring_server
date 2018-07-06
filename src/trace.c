/*
** EPITECH PROJECT, 2018
** irc
** File description:
** trace fction
*/

#include <stdio.h>
#include <stdarg.h>

#include "trace.h"
#include "colors.h"

struct trace_s {
	char *fr;
	const char *front;
	char *end;
	int fd;
};

static const struct trace_s TRACE_TAB[] = {
	{ "[", BOLDYELLOW "Info", "]", 1},
	{ "{-", BOLDMAGENTA "Debug" , "-}", 1},
	{ "/", BOLDRED "Error" , "\\", 2},
	{ "<!>", BOLDRED "PANIC" , ":", 2},
	{ "--", BOLDGREEN "Ack", "--", 1 },
	{ "#", BOLDWHITE "Dump", "", 1 },
	{ "", "", "", 1 },
	{ BOLDYELLOW, "->", RESET, 1 },
};

int trace(enum trace_error_type_e type, const char *format, ...)
{
	va_list ap;
	int ret_value;

#ifndef DEBUG
	if (type == T_DEBUG)
		return (0);
#endif
	va_start(ap, format);
	ret_value = dprintf(TRACE_TAB[type].fd, "\r%s%s%s%s ", TRACE_TAB[type].fr, TRACE_TAB[type].front, RESET, TRACE_TAB[type].end);
	ret_value += vdprintf(TRACE_TAB[type].fd, format, ap);
	va_end(ap);
	return (ret_value);
}
