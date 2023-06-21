#include "shell.h"

/**
 * get_history_file - this function gets the history file
 * @info: this is the parameter for struct
 *
 * Return: the allocated string containing the history file
 */
char *get_history_file(info_t *info)
{
	char *buffer, *direct;

	direct = _getenv(info, "HOME=");
	if (!direct)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, direct);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - this creates a file, or appends to an existing file
 * @info: this is the parameter for struct
 *
 * Return: 1 on success, otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t fdd;
	char *file_name = get_history_file(info);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	fdd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fdd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fdd);
		_putfd('\n', fdd);
	}
	_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - this function reads history from a file
 * @info: this is the parameter for struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int s, last = 0, linecount = 0;
	ssize_t fdd, rdlength, fsize = 0;
	struct stat st;
	char *buffer = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fdd = open(file_name, O_RDONLY);
	free(file_name);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlength = read(fdd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(fdd);
	for (s = 0; s < fsize; s++)
		if (buffer[s] == '\n')
		{
			buffer[s] = 0;
			build_history_list(info, buffer + last, linecount++);
			last = s + 1;
		}
	if (last != s)
		build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - this adds input to a history linked list
 * @info: this is a structure containing potential arguments
 * @buf: this is a buffer
 * @linecount: this is the history linecount, histcount
 *
 * Return: Always 0 (success)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - this function renumbers the
 * history linked list after changes
 * @info: this structure contains potential arguments
 *
 * Return: the new histcount after changes
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int s = 0;

	while (node)
	{
		node->num = s++;
		node = node->next;
	}
	return (info->histcount = s);
}
