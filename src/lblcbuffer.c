/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** Create
*/

#include <stdlib.h>

#include "lblcbuffer.h"

static size_t lblcbuffer_read(lblcbuffer *buffer, char *dest, size_t count)
{
	size_t i;

	if (buffer->writer == buffer->reader && buffer->empty == true)
		return (0);
	for (i = 0; i < count; ++i) {
		dest[i] = *buffer->reader;
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

static size_t lblcbuffer_write(lblcbuffer *buffer, const char *src, size_t count)
{
	size_t i;

	if (buffer->writer == buffer->reader && buffer->empty == false)
		return (0);
	if (count)
		buffer->empty = false;
	for (i = 0; i < count; ++i) {
		*buffer->writer = src[i];
		++buffer->writer;
		if (buffer->writer >= buffer->end)
			buffer->writer = buffer->buffer;
		if (buffer->writer == buffer->reader)
			return (i + 1);
	}
	return (i);
}

static void lblcbuffer_destroy(lblcbuffer *buffer)
{
	free(buffer->buffer);
}

static size_t lblcbuffer_lsize(lblcbuffer *buffer)
{
	if (buffer->reader < buffer->writer)
		return (buffer->end - buffer->writer +
			buffer->reader - buffer->buffer);
	else if (buffer->reader > buffer->writer)
		return (buffer->reader - buffer->writer);
	return ((buffer->empty) ? buffer->size : 0);
}

ssize_t lblcbuffer_getbytes(lblcbuffer *buffer, char **pline, char delim)
{
	size_t rd;
	char *p = buffer->reader;

	if (p == buffer->writer) {
		*pline = NULL;
		return (0);
	}
	for (rd = 1; *p != delim && p != buffer->writer; ++rd) {
		if (p == buffer->end)
			p = buffer->buffer;
		++p;
	}
	*pline = calloc(rd + 1, sizeof(char));
	if (*pline == NULL)
		return (-1);
	buffer->read(buffer, *pline, rd);
	return (rd);
}

int lblcbuffer_create(lblcbuffer *buffer, size_t size)
{
	buffer->buffer = calloc(1, size);
	if (buffer->buffer == NULL)
		return (-1);
	buffer->size = size;
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->end = buffer->buffer + buffer->size;
	buffer->empty = true;
	buffer->read = lblcbuffer_read;
	buffer->destroy = lblcbuffer_destroy;
	buffer->write = lblcbuffer_write;
	buffer->lsize = lblcbuffer_lsize;
	buffer->getbytes = lblcbuffer_getbytes;
	return (0);
}
