/*
** my_str_to_wordtab.c for str_wordtab in /home/leandre/libmy
**
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
**
** Started on  Wed Apr 26 19:18:18 2017 Léandre Blanchard
** Last update Sun Jan  7 10:39:50 2018 Léandre Blanchard
*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static size_t max_len(const char *str, const char *delim)
{
	size_t len = 1;

	for (size_t i = 0; str[i]; ++i)
		for (size_t j = 0; delim[j]; ++j)
			if (str[i] == delim[j])
				++len;
	return (len);
}

size_t tablen(void *tab)
{
	void **p = tab;
	size_t size;

	for (size = 0; p[size] != NULL; ++size);
	return (size);
}

void free_tab(void *tab)
{
	void **p = tab;

	for (size_t i = 0; p[i] != NULL; ++i)
		free(p[i]);
	free(p);
}

char **wordtab(const char *str, const char *delim)
{
	char **tab = NULL;
	size_t len = max_len(str, delim);
	char *dup = strdup(str);

	if (!dup)
		return (NULL);
	tab = calloc(len + 1, sizeof(char *));
	str = strtok(dup, delim);
	for (size_t i = 0; str != NULL; ++i) {
		tab[i] = strdup(str);
		str = strtok(NULL, delim);
	}
	free(dup);
	return (tab);
}
