/*
** EPITECH PROJECT, 2018
** zappy server
** File description:
** trace header
*/

#ifndef TRACE_H_
# define TRACE_H_

enum trace_error_type_e {
	T_INFO,
	T_DEBUG,
	T_ERROR,
	T_PANIC,
	T_ACK,
	T_DUMP,
	T_NONE,
	T_PROMPT,
};

int trace(enum trace_error_type_e type, const char *format, ...);

#endif /* !TRACE_H_ */
