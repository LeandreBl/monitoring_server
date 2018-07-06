/*
** EPITECH PROJECT, 2018
** lbl generic tab
** File description:
** generic C arrays
*/

#include <stdlib.h>
#include <string.h>

#include "lblgtab.h"

void gtab_destroy(gtab_t *gtab, void (* ifct)(void *))
{
	if (ifct != NULL)
		while (gtab->len > 0)
			gtab_remove_at(gtab, gtab->len - 1, ifct);
	free(gtab->i);
}

int gtab_resize(gtab_t *gtab, size_t newsize, void (* ifct)(void *))
{
	if (newsize == gtab->max_size)
		return (0);
	for (size_t i = newsize; i < gtab->len; ++i)
		gtab_remove_at(gtab, i - 1, ifct);
	gtab->max_size = newsize;
	if (newsize < gtab->len)
		gtab->len = newsize;
	gtab->i = realloc(gtab->i, gtab->max_size * sizeof(void *));
	if (gtab->i == NULL)
		return (-1);
	return (0);
}

int gtab_append(gtab_t *gtab, void *add)
{
	if (gtab->len == gtab->max_size &&
		gtab_resize(gtab, gtab->len + GTAB_REALLOC_SIZE, NULL) == -1)
		return (-1);
	gtab->i[gtab->len] = add;
	++gtab->len;
	return (0);
}

int gtab_append_at(gtab_t *gtab, void *add, size_t index)
{
	if (index > gtab->len || (gtab->len == gtab->max_size &&
		gtab_resize(gtab, gtab->len + GTAB_REALLOC_SIZE, NULL) == -1))
		return (-1);
	for (size_t i = gtab->len; i > index; --i)
		gtab->i[i] = gtab->i[i - 1];
	gtab->i[index] = add;
	++gtab->len;
	return (0);
}

void gtab_remove(gtab_t *gtab, void *ptr, void (* ifct)(void *))
{
	for (size_t i = 0; i < gtab->len; ++i)
		if (gtab->i[i] == ptr)
			gtab_remove_at(gtab, i, ifct);
}

void gtab_remove_at(gtab_t *gtab, size_t index, void (* ifct)(void *))
{
	if (index > gtab->len)
		return;
	if (ifct != NULL)
		ifct(gtab->i[index]);
	for (size_t i = index; i < gtab->len - 1; ++i)
		gtab->i[i] = gtab->i[i + 1];
	--gtab->len;
}

int gtab_shrink_to_fit(gtab_t *gtab)
{
	if (gtab->len != gtab->max_size) {
		gtab->max_size = gtab->len;
		gtab->i = realloc(gtab->i, gtab->len * sizeof(void *));
		if (gtab->i == NULL)
			return (-1);
	}
	return (0);
}

void gtab_swap(gtab_t *gtab, size_t p1, size_t p2)
{
	void *tmp;

	if (p1 >= gtab->len || p2 >= gtab->len)
		return;
	tmp = gtab->i[p1];
	gtab->i[p1] = gtab->i[p2];
	gtab->i[p2] = tmp;
}

int gtab_create(gtab_t *gtab, size_t nsize)
{
	gtab->i = malloc(nsize * sizeof(void *));
	if (gtab->i == NULL)
		return (-1);
	gtab->max_size = nsize;
	gtab->len = 0;
	return (0);
}
