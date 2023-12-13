#include "shell.h"

/**
 * _strcpy - copies a string
 * @st_dest: destination
 * @src_string: source
 * Return: pointer
 */

char *_strcpy(char *st_dest, char *src_string)
{
	int i = 0;

	if (st_dest == src_string || src_string == 0)
		return (st_dest);
	while (src_string[i])
	{
		st_dest[i] = src_string[i];
		i++;
	}
	st_dest[i] = 0;
	return (st_dest);
}

/**
 * _strdup - duplicates a string
 * @_str: the string
 * Return: pointer
 */

char *_strdup(const char *_str)
{
	int length = 0;
	char *ret;

	if (_str == NULL)
		return (NULL);
	while (*_str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--_str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: string
 * Return: Nothing
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
