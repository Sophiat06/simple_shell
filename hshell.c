#include "shell.h"

/**
 * hsh - this is the main shell loop function
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int built_rest = 0;

	while (a != -1 && built_rest != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			built_rest = find_builtin(info);
			if (built_rest == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (built_rest == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_rest);
}

/**
 * find_builtin - this function finds a builtin command
 * @info: this is the parameter & return info struct
 *
 * Return: -1 if builtin is not found,
 * 0 if builtin executed successfully,
 * 1 if builtin is found but7 not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int s, built_in_rest = -1;
	builtin_table builtintabl[] = {
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

	for (s = 0; builtintabl[s].type; s++)
		if (_strcmp(info->argv[0], builtintabl[s].type) == 0)
		{
			info->line_count++;
			built_in_rest = builtintabl[s].func(info);
			break;
		}
	return (built_in_rest);
}

/**
 * find_cmd - this function finds a command in PATH
 * @info: this is a parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int s, z;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (s = 0, z = 0; info->arg[s]; s++)
		if (!is_delim(info->arg[s], " \t\n"))
			z++;
	if (!z)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - this function forks a an execev thread to run cmd
 * @info: this is a parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t baby_pid;

	baby_pid = fork();
	if (baby_pid == -1)
	{
		/* TODO: PUT FUNCTION ERROR */
		perror("Error:");
		return;
	}
	if (baby_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT FUNCTION ERROR */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
