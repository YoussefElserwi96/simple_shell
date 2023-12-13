#include "shell.h"

/**
 * _strlen - length of string
 * @s: string
 * Return: length
 */

int _strlen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}

/**
 * _strcmp -  comparing two strings
 * @string1 : string 1
 * @string2 : string 2
 * Return: - ! s1 < s2, + ! s1 > s2, 0 ! s1 == s2
 */

int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_with - check if start with heystack
 * @h_stack: string
 * @sub_string: substring
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *h_stack, const char *sub_string)
{
	while (*sub_string)
		if (*sub_string++ != *h_stack++)
			return (NULL);
	return ((char *)h_stack);
}

/**
 * _strcat - concatenates two strings
 * @d_buffer: destination buffer
 * @src_buffer: source buffer
 * Return: pointer
 */

char *_strcat(char *d_buffer, char *src_buffer)
{
	char *ret = d_buffer;

	while (*d_buffer)
		d_buffer++;
	while (*src_buffer)
		*d_buffer++ = *src_buffer++;
	*d_buffer = *src_buffer;
	return (ret);
}
