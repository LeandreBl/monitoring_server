/*
** EPITECH PROJECT, 2018
** lbl generic tab
** File description:
** generic C arrays
*/

#ifndef LBL_GTAB_H_
# define LBL_GTAB_H_

# include <stddef.h>

# define GTAB_REALLOC_SIZE (5)

typedef struct lblgtab_s {
	size_t max_size;
	size_t len;
	void **i;
} gtab_t;

int gtab_create(gtab_t *gtab, size_t nsize);
void gtab_destroy(gtab_t *gtab, void (* ifct)(void *));
int gtab_resize(gtab_t *gtab, size_t newsize, void (* ifct)(void *));
int gtab_append(gtab_t *gtab, void *add);
int gtab_append_at(gtab_t *gtab, void *add, size_t index);
void gtab_remove(gtab_t *gtab, void *remove, void (* ifct)(void *));
void gtab_remove_at(gtab_t *gtab, size_t index, void (* ifct)(void *));
int gtab_shrink_to_fit(gtab_t *gtab);
void gtab_swap(gtab_t *gtab, size_t p1, size_t p2);

#endif /* !LBL_GTAB_H_ */
