/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** Create
*/

#include <stdlib.h>

#include "lblcbuffer.h"

size_t cbuffer_read(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t i;
	char *p = dest;

	if (buffer->writer == buffer->reader && buffer->empty == true)
		return (0);
	for (i = 0; i < count; ++i) {
		p[i] = *buffer->reader;
		++buffer->reader;
		if (buffer->reader >= buffer->end)
			buffer->reader = buffer->buffer;
		if (buffer->reader == buffer->writer) {
			buffer->empty = true;
			return (i + 1);
		}
	}
	return (i);
}

size_t cbuffer_write(cbuffer_t *buffer, const void *src, size_t count)
{
	size_t i;
	const char *p = src;

	if (buffer->writer == buffer->reader && buffer->empty == false)
		return (0);
	if (count)
		buffer->empty = false;
	for (i = 0; i < count; ++i) {
		*buffer->writer = p[i];
		++buffer->writer;
		if (buffer->writer >= buffer->end)
			buffer->writer = buffer->buffer;
		if (buffer->writer == buffer->reader)
			return (i + 1);
	}
	return (i);
}

void cbuffer_destroy(cbuffer_t *buffer)
{
	free(buffer->buffer);
}

size_t cbuffer_lsize(cbuffer_t *buffer)
{
	if (buffer->reader < buffer->writer)
		return (buffer->end - buffer->writer +
			buffer->reader - buffer->buffer);
	else if (buffer->reader > buffer->writer)
		return (buffer->reader - buffer->writer);
	return ((buffer->empty) ? buffer->size : 0);
}

ssize_t cbuffer_getbytes(cbuffer_t *buffer, char **pline, char delim)
{
	size_t rd;
	char *p = buffer->reader;

	if (p == buffer->writer) {
		*pline = NULL;
		return (0);
	}
	for (rd = 1; p != buffer->writer && *p != delim; ++rd) {
		if (p == buffer->end)
			p = buffer->buffer;
		++p;
	}
	*pline = calloc(rd + 1, sizeof(char));
	if (*pline == NULL)
		return (-1);
	cbuffer_read(buffer, *pline, rd);
	return (rd);
}

int cbuffer_create(cbuffer_t *buffer, size_t size)
{
	buffer->buffer = malloc(size);
	if (buffer->buffer == NULL)
		return (-1);
	buffer->size = size;
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->end = buffer->buffer + buffer->size;
	buffer->empty = true;
	return (0);
}
