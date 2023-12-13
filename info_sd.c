#include "shell.h"

/**
 * clear_info - to inti info struct
 * @info: stru add
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - to inti info struct
 * @strc_info: stru add
 * @arg_vec: arg vec
 */

void set_info(info_t *strc_info, char **arg_vec)
{
	int i = 0;

	strc_info->fname = arg_vec[0];
	if (strc_info->arg)
	{
		strc_info->argv = strtow(strc_info->arg, " \t");
		if (!strc_info->argv)
		{

			strc_info->argv = malloc(sizeof(char *) * 2);
			if (strc_info->argv)
			{
				strc_info->argv[0] = _strdup(strc_info->arg);
				strc_info->argv[1] = NULL;
			}
		}
		for (i = 0; strc_info->argv && strc_info->argv[i]; i++)
			;
		strc_info->argc = i;

		replace_alias(strc_info);
		replace_vars(strc_info);
	}
}

/**
 * free_info - frees info_t
 * @info: str add
 * @all: freeing field
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
