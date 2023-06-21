#include "shell.h"

/**
 * _myhistory - This displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: This is the Structure containing
 * potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - This sets alias to string
 * @info: The parameter struct
 * @str: This is the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *m, o;
	int ret;

	m = _strchr(str, '=');
	if (!p)
		return (1);
	o = *m;
	*m = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*m = o;
	return (ret);
}

/**
 * set_alias - This sets alias to string
 * @info: The parameter struct
 * @str: This is the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *m;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - This prints an alias string
 * @node: This the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *m = NULL, *a = NULL;

	if (node)
	{
		m = _strchr(node->str, '=');
		for (a = node->str; a <= m; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(m + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - This mimics the alias builtin (man alias)
 * @info: This is Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *m = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		m = _strchr(info->argv[i], '=');
		if (m)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
