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

typedef struct lblgtab_s lblgtab;

struct lblgtab_s {
	size_t max_size;
	size_t len;
	void **i;
	void (* destroy)(lblgtab *gtab, void (* ifct)(void *));
	int (* resize)(lblgtab *gtab, size_t newsize, void (* ifct)(void *));
	int (* append)(lblgtab *gtab, void *add);
	int (* append_at)(lblgtab *gtab, void *add, size_t index);
	void (* remove)(lblgtab *gtab, void *remove, void (* ifct)(void *));
	void (* remove_at)(lblgtab *gtab, size_t index, void (* ifct)(void *));
	int (* shrink_to_fit)(lblgtab *gtab);
	void (* swap)(lblgtab *gtab, size_t p1, size_t p2);
};

int lblgtab_create(lblgtab *gtab, size_t nsize);

#endif /* !LBL_GTAB_H_ */