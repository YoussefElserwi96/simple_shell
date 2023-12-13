#include "shell.h"

/**
 * _erratoi - string to an integer
 * @chng_strng: string to change
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error
 */

int _erratoi(char *chng_strng)
{
	int i = 0;
	unsigned long int result = 0;

	if (*chng_strng == '+')
		chng_strng++;
	for (i = 0;  chng_strng[i] != '\0'; i++)
	{
		if (chng_strng[i] >= '0' && chng_strng[i] <= '9')
		{
			result *= 10;
			result += (chng_strng[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints error if there
 * @i_prams: the params and info struc
 * @err_strng: string
 * Return: 0 if no numbers in string,
 * converted number otherwise -1 on error
 */

void print_error(info_t *i_prams, char *err_strng)
{
	_eputs(i_prams->fname);
	_eputs(": ");
	print_d(i_prams->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(i_prams->argv[0]);
	_eputs(": ");
	_eputs(err_strng);
}

/**
 * print_d - decimal number base 10
 * @i_put0: input
 * @f_desc: the filedescriptor
 * Return: number of characters printed
 */

int print_d(int i_put0, int f_desc)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (f_desc == STDERR_FILENO)
		__putchar = _eputchar;
	if (i_put0 < 0)
	{
		_abs_ = -i_put0;
		__putchar('-');
		count++;
	}
	else
		_abs_ = i_put0;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - convert func
 * @num: number
 * @base: base
 * @flags: arg flags
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - func to replace
 * @buf: string to be changed
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
