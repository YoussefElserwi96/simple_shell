#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest_strng: destination
 *@src_strng: source
 *@c_n: characters
 *Return: the copied string
 */

char *_strncpy(char *dest_strng, char *src_strng, int c_n)
{
	int i, j;
	char *s = dest_strng;

	i = 0;
	while (src_strng[i] != '\0' && i < c_n - 1)
	{
		dest_strng[i] = src_strng[i];
		i++;
	}
	if (i < c_n)
	{
		j = i;
		while (j < c_n)
		{
			dest_strng[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest_02: first string
 *@src_strng02: 2nd string
 *@n_bytes: bytes
 *Return: string
 */

char *_strncat(char *dest_02, char *src_strng02, int n_bytes)
{
	int i, j;
	char *s = dest_02;

	i = 0;
	j = 0;
	while (dest_02[i] != '\0')
		i++;
	while (src_strng02[j] != '\0' && j < n_bytes)
	{
		dest_02[i] = src_strng02[j];
		i++;
		j++;
	}
	if (j < n_bytes)
		dest_02[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@strng: string to be parsed
 *@chr: character to look for
 *Return: pointer
 */

char *_strchr(char *strng, char chr)
{
	do {
		if (*strng == chr)
			return (strng);
	} while (*strng++ != '\0');

	return (NULL);
}
