#include "shell.h"

/**
 *_eputs - to print in str
 * @i_str: the string
 * Return: Nothing
 */

void _eputs(char *i_str)
{
	int i = 0;

	if (!i_str)
		return;
	while (i_str[i] != '\0')
	{
		_eputchar(i_str[i]);
		i++;
	}
}

/**
 * _eputchar - send char to stdr
 * @c: char to print
 * Return: On success 1.
 * On error, -1 is returned
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - char to fdesc
 * @c: char
 * @fl_desc: filedescriptor
 * Return: On success 1.
 * On error, -1 is returned
 */

int _putfd(char c, int fl_desc)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fl_desc, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prt in str
 * @str: the string
 * @fd: filedesc
 * Return: the number of chars
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
