#include "shell.h"

/**
 * **strtow - splits a string into words
 * @i_strng: input string
 * @d_strng: delimeter string
 * Return: a pointer
 */

char **strtow(char *i_strng, char *d_strng)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (i_strng == NULL || i_strng[0] == 0)
		return (NULL);
	if (!d_strng)
		d_strng = " ";
	for (i = 0; i_strng[i] != '\0'; i++)
		if (!is_delim(i_strng[i], d_strng) && (is_delim(i_strng[i + 1], d_strng) || !i_strng[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(i_strng[i], d_strng))
			i++;
		k = 0;
		while (!is_delim(i_strng[i + k], d_strng) && i_strng[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = i_strng[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits string into words
 * @i_str2: input string
 * @d_strng2: delimeter
 * Return: a pointer
 */

char **strtow2(char *i_str2, char d_strng2)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (i_str2 == NULL || i_str2[0] == 0)
		return (NULL);
	for (i = 0; i_str2[i] != '\0'; i++)
		if ((i_str2[i] != d_strng2 && i_str2[i + 1] == d_strng2) ||
			(i_str2[i] != d_strng2 && !i_str2[i + 1]) || i_str2[i + 1] == d_strng2)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (i_str2[i] == d_strng2 && i_str2[i] != d_strng2)
			i++;
		k = 0;
		while (i_str2[i + k] != d_strng2 && i_str2[i + k] && i_str2[i + k] != d_strng2)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = i_str2[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
