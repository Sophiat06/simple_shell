#include "shell.h"

/**
 * list_len - This func determines length of a linked list
 * @h: This is a pointer to the first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * list_to_strings - This func returns an array of strings of the list->str
 * @head: This is a pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t b = list_len(head), n;
	char **strs;
	char *str;

	if (!head || !b)
		return (NULL);
	strs = malloc(sizeof(char *) * (b + 1));
	if (!strs)
		return (NULL);
	for (b = 0; node; node = node->next, b++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < b; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[b] = str;
	}
	strs[b] = NULL;
	return (strs);
}

/**
 * print_list - This func prints all elements of a list_t linked list
 * @h: This is a pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * node_starts_with - This func returns node whose string starts with prefix
 * @node: This is a pointer to list head
 * @prefix: This is the string to match
 * @c: This is the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *s = NULL;

	while (node)
	{
		s = starts_with(node->str, prefix);
		if (s && ((c == -1) || (*s == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This func gets the index of a node
 * @head: This is a pointer to list head
 * @node: This is a pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t b = 0;

	while (head)
	{
		if (head == node)
			return (b);
		head = head->next;
		b++;
	}
	return (-1);
}
