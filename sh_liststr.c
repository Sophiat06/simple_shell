#include "shell.h"

/**
 * add_node - this function adds a node to the start of the list
 * @head: this is an address of pointer to head node
 * @str: this is the str field of node
 * @num: this is a node index used by history
 *
 * Return: the size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newheads;

	if (!head)
		return (NULL);
	newheads = malloc(sizeof(list_t));
	if (!newheads)
		return (NULL);
	_memset((void *)newheads, 0, sizeof(list_t));
	newheads->num = num;
	if (str)
	{
		newheads->str = _strdup(str);
		if (!newheads->str)
		{
			free(newheads);
			return (NULL);
		}
	}
	newheads->next = *head;
	*head = newheads;
	return (newheads);
}

/**
 * add_node_end - this function adds a node to the end of the list
 * @head: this is the address of pointer to head node
 * @str: this is the str field of node
 * @num: this is a node index used by history
 *
 * Return: the size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newnode, *old_node;

	if (!head)
		return (NULL);

	old_node = *head;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (old_node)
	{
		while (old_node->next)
			old_node = old_node->next;
		old_node->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}

/**
 * print_list_str - this function prints only the str
 * element of a list_t linked list
 * @h: this is a pointer to the first node
 *
 * Return: the size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * delete_node_at_index - this function deletes node at a given index
 * @head: this is the address of the pointer to the first node
 * @index: the index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int s = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (s == index)
		{
			previous_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		s++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - this function frees all nodes in a list
 * @head_ptr: this is the address of a pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nodes, *nxt_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nodes = head;
	while (nodes)
	{
		nxt_node = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = nxt_node;
	}
	*head_ptr = NULL;
}
