#include "shell.h"

/**
 * hsh - main shell props and loops of the shell
 * @_info00: the params and info struc
 * @arg_vec: arg vector
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *_info00, char **arg_vec)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(_info00);
		if (interactive(_info00))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(_info00);
		if (r != -1)
		{
			set_info(_info00, arg_vec);
			builtin_ret = find_builtin(_info00);
			if (builtin_ret == -1)
				find_cmd(_info00);
		}
		else if (interactive(_info00))
			_putchar('\n');
		free_info(_info00, 0);
	}
	write_history(_info00);
	free_info(_info00, 1);
	if (!interactive(_info00) && _info00->status)
		exit(_info00->status);
	if (builtin_ret == -2)
	{
		if (_info00->err_num == -1)
			exit(_info00->status);
		exit(_info00->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - to find a builtin command
 * @_info01: the params and info struc
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *_info01)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(_info01->argv[0], builtintbl[i].type) == 0)
		{
			_info01->line_count++;
			built_in_ret = builtintbl[i].func(_info01);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command
 * @_info02: the params and info struc
 * Return: void
 */

void find_cmd(info_t *_info02)
{
	char *path = NULL;
	int i, k;

	_info02->path = _info02->argv[0];
	if (_info02->linecount_flag == 1)
	{
		_info02->line_count++;
		_info02->linecount_flag = 0;
	}
	for (i = 0, k = 0; _info02->arg[i]; i++)
		if (!is_delim(_info02->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(_info02, _getenv(_info02, "PATH="), _info02->argv[0]);
	if (path)
	{
		_info02->path = path;
		fork_cmd(_info02);
	}
	else
	{
		if ((interactive(_info02) || _getenv(_info02, "PATH=")
			|| _info02->argv[0][0] == '/') && is_cmd(_info02, _info02->argv[0]))
			fork_cmd(_info02);
		else if (*(_info02->arg) != '\n')
		{
			_info02->status = 127;
			print_error(_info02, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec
 * @_info03: the params and info struc
 * Return: void
 */

void fork_cmd(info_t *_info03)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(_info03->path, _info03->argv, get_environ(_info03)) == -1)
		{
			free_info(_info03, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(_info03->status));
		if (WIFEXITED(_info03->status))
		{
			_info03->status = WEXITSTATUS(_info03->status);
			if (_info03->status == 126)
				print_error(_info03, "Permission denied\n");
		}
	}
}
