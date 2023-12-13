#include "shell.h"

/**
 * main - entry point
 * @a_c: arg_count
 * @a_v: arg_vec
 * Return: 0 on success, 1 on error
 */

int main(int a_c, char **a_v)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (a_c == 2)
	{
		fd = open(a_v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(a_v[0]);
				_eputs(": 0: Can't open ");
				_eputs(a_v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, a_v);
	return (EXIT_SUCCESS);
}
