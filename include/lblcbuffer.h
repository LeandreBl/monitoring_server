/*
** EPITECH PROJECT, 2018
** circular_buffer API
** File description:
** C circular buffer API
*/

#ifndef LBL_CIRCULAR_BUFFER_API_
# define LBL_CIRCULAR_BUFFER_API_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

struct cbuffer_s {
	char *reader;
	char *writer;
	char *end;
	char *buffer;
	size_t size;
	bool empty;
	void (* destroy)(struct cbuffer_s *self);
	size_t (* write)(struct cbuffer_s *self, const char *src, size_t count);
	size_t (* read)(struct cbuffer_s *self, char *src, size_t count);
	size_t (* lsize)(struct cbuffer_s *self);
	ssize_t (* getbytes)(struct cbuffer_s *self, char **pptr, char delim);
};

typedef struct cbuffer_s lblcbuffer;

int lblcbuffer_create(lblcbuffer *buffer, size_t size);

#endif /* !LBL_CIRCULAR_BUFFER_API_ */
