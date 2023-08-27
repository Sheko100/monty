#include "monty.h"

/**
 * issame - checks if two strings are identical
 * @s1: first string
 * @s2: second string
 *
 * Return: 1 if they are identical
 * 0 otherwise
 */

int issame(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] || *s2)
	{
		if (s1[i] != *s2)
			return (0);
		s2++;
		i++;
	}

	return (1);
}

/**
 * isnum - checks if the string is a num
 * @num: string of a number
 *
 * Return: 1 if it's a number
 * 0 otherwise
 */
int isnum(char *num)
{
	int i = 0;

	if (num != NULL)
	{
		if (num[i] == '-')
			i++;
		while (num[i])
		{
			if (num[i] < 48 || num[i] > 57)
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}
