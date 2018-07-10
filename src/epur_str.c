/*
** epur_str.c for epur_str in /home/leandre/libmy
**
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
**
** Started on  Mon Mar 13 14:38:15 2017 Léandre Blanchard
** Last update Sun Jan  7 09:52:41 2018 Léandre Blanchard
*/

#include <string.h>

static void shift_l(char *str)
{
	for (int i = 0; str[i] != 0; ++i)
		str[i] = str[i + 1];
}

static void shift_r(char *str)
{
	size_t len = strlen(str);

	if (len > 0)
		str[len - 1] = 0;
}

void epur_str(char *str)
{
	int i;

	if (str == NULL)
		return;
	for (i = 0; str[i] == ' ' || str[i] == '\t'; ++i)
		shift_l(str);
	while (str[i] != 0) {
		while ((str[i] == ' ' || str[i] == '\t')
		       && (str[i + 1] == ' ' || str[i + 1] == '\t'))
			shift_l(str + i);
		++i;
	}
	if (strlen(str) > 0)
		while (str[strlen(str) - 1] == ' ' || str[strlen(str) - 1] == '\t')
			shift_r(str);
}
