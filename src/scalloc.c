/*
** EPITECH PROJECT, 2018
** irc
** File description:
** scalloc
*/

#include <stdlib.h>
#include <stdint.h>

#include "trace.h"

int scalloc(void *ptr, size_t nmemb, size_t size)
{
	void **p = ptr;

	*p = calloc(nmemb, size);
	if (*p == NULL) {
		trace(T_PANIC, "Not enough memory.\n");
		return (-1);
	}
	return (0);
}
