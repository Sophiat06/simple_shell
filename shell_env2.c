#include "shell.h"

/**
 * get_environ - this returns the string array copy of our environ
 * @info: this is the structure containing potential arguments
 * used to maintain constant function prototype
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - this removes an environment variable
 * @info: this is a structure containing potential arguments used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string environment var
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t s = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), s);
			s = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		s++;
	}
	return (info->env_changed);
}

/**
 * _setenv - this function initializes a new environ variable,
 * or modify an existing one
 * @info: the structure that contains potential arguments used to maintain
 * constant function prototypes.
 * @var: this is the string environment variable property
 * @value: this is the string environment variable value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
