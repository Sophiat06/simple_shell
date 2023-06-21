#include "shell.h"

/**
 * _myenv - This prints the current environment
 * @info: This Structure contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This gets the value of an environ variable
 * @info: This Structure contains potential arguments. Used to maintain
 * @name: This is the env var name
 *
 * Return: This is the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *n;

	while (node)
	{
		n = starts_with(node->str, name);
		if (n && *n)
			return (n);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This Initialize a new environment variable,
 * or modify an existing one
 * @info: This Structure contains potential arguments. Used to maintain
 *  constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - This Removes an environment variable
 * @info: This Structure contains potential arguments. Used to maintain
 *  constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * populate_env_list - This populates env linked list
 * @info: This Structure contains potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}
