#include "shell.h"

/**
 * interactive - true if shell in inreractive
 * @s_address: struct address
 * Return: 1 if interactive mode, 0 if not
 */

int interactive(info_t *s_address)
{
	return (isatty(STDIN_FILENO) && s_address->readfd <= 2);
}

/**
 * is_delim - to check if char is a delimeter
 * @c_char: char to be checked
 * @d_strng: deli string
 * Return: 1 if true, 0 if false
 */

int is_delim(char c_char, char *d_strng)
{
	while (*d_strng)
		if (*d_strng++ == c_char)
			return (1);
	return (0);
}

/**
 *_isalpha - to checks alphabetical chars
 *@i_c01: character
 *Return: 1 if i_c01 is alphabetic, 0 if not
 */

int _isalpha(int i_c01)
{
	if ((i_c01 >= 'a' && i_c01 <= 'z') || (i_c01 >= 'A' && i_c01 <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a str to int
 *@s_string03: the string
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s_string03)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s_string03[i] != '\0' && flag != 2; i++)
	{
		if (s_string03[i] == '-')
			sign *= -1;

		if (s_string03[i] >= '0' && s_string03[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s_string03[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
