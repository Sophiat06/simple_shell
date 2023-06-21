#include "shell.h"

/**
 * _myexit -this exits the shell
 * @info: this is the structure containing potential arguments for
 * constant function prototype.
 * Return: this exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_checker;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_checker = _erratoi(info->argv[1]);
		if (exit_checker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - this changes the current directory of the process
 * @info: the structure containing potential arguments
 * constant function prototype.
 * Return: Always 0 (success)
 */
int _mycd(info_t *info)
{
	char *q, *direct, buffer[1024];
	int chdir_ret;

	q = getcwd(buffer, 1024);
	if (!q)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!direct)
			chdir_ret = /* TODO: what should this be? */
				chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			chdir_ret = chdir(direct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(q);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - this function changes the current directory of the process
 * @info: the structure containing potential arguments used in maintaining the
 * constant function prototype.
 * Return: Always 0 (success)
 */
int _myhelp(info_t *info)
{
	char **arg_arrays;

	arg_arrays = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arrays); /* temp att_unused workaround */
	return (0);
}
