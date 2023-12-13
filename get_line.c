#include "shell.h"

/**
 * input_buf - buff chain command
 * @pram_strct: param struct
 * @buf: addr buff
 * @len: address lenvar
 * Return: bytes
 */

ssize_t input_buf(info_t *pram_strct, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(pram_strct, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			pram_strct->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(pram_strct, *buf, pram_strct->histcount++);
			{
				*len = r;
				pram_strct->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - line minus newline
 * @i_strct: param stru
 * Return: bytes
 */

ssize_t get_input(info_t *i_strct)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(i_strct->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(i_strct, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(i_strct, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(i_strct, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			i_strct->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - to read buffer
 * @info: param stru
 * @buf: buffer
 * @i: size
 * Return: rjujoik
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - inout stdn
 * @info: param stru
 * @ptr: address of pointer
 * @length: size of preallocated ptr
 * Return: shio
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - to blocks ctrl-C
 * @sig_num: signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
