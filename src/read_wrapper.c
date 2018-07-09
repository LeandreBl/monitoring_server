/*
** EPITECH PROJECT, 2018
** cobra server
** File description:
** read_wrapper
*/

#include <unistd.h>
#include <stddef.h>

ssize_t read_wrapper(int fd, void *dest, size_t size)
{
	ssize_t rd;
	size_t total = 0;

	do {
		rd = read(fd, dest + total, size - total);
		if (rd == -1 || (rd == 0 && size - total != 0))
			return (-1);
		total += rd;
	} while (total < size);
	return (total);
}