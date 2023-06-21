#include "shell.h"

/**
 * is_chain - this tests if current char in buffer is a chain delimeter
 * @info: this is the parameter struct
 * @buf: this is the char buffer
 * @p: the address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - this checks if we should continue chaining
 * based on last status
 * @info: this is the parameter struct
 * @buf: this is the char buffer
 * @p: this is the address of current position in buffer
 * @i: the starting position in buffer
 * @len: the length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * replace_alias -this replaces the alias in the token string
 * @info: this is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int s;
	list_t *node;
	char *p;

	for (s = 0; s < 10; s++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - this replaces the vars in the token string
 * @info: this is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int s = 0;
	list_t *node;

	for (s = 0; info->argv[s]; s++)
	{
		if (info->argv[s][0] != '$' || !info->argv[s][1])
			continue;

		if (!_strcmp(info->argv[s], "$?"))
		{
			replace_string(&(info->argv[s]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[s], "$$"))
		{
			replace_string(&(info->argv[s]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[s][1], '=');
		if (node)
		{
			replace_string(&(info->argv[s]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[s], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - this replaces a string
 * @old: this is the address of old string
 * @new: this is a new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
