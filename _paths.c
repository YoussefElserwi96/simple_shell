#include "shell.h"

/**
 * is_cmd -to check if excut
 * @i_strct: info_struct
 * @path: path
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(info_t *i_strct, char *path)
{
	struct stat st;

	(void)i_strct;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @p_strng: P_string
 * @strt_in: start I
 * @stp_ind: stop I
 * Return: pointer to new buffer
 */

char *dup_chars(char *p_strng, int strt_in, int stp_ind)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = strt_in; i < stp_ind; i++)
		if (p_strng[i] != ':')
			buf[k++] = p_strng[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - to find cmf strng
 * @inf_strct: info struct
 * @path_of_str: Pstring
 * @cmd: cmd to find
 * Return: full path of cmd if found or NULL
 */

char *find_path(info_t *inf_strct, char *path_of_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_of_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf_strct, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_of_str[i] || path_of_str[i] == ':')
		{
			path = dup_chars(path_of_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf_strct, path))
				return (path);
			if (!path_of_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
