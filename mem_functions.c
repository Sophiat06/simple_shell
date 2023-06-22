#include "shell.h"

/**
 **_memset - this function fills memory with a constant byte space
 *@s: this is a  pointer to the memory area
 *@b: this is the byte to fill *s with
 *@n: the number of bytes to be used
 *Return: (s) as a pointer to the memory area of s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - this function frees a string of strings
 * @pp: this is the string of strings
 */
void ffree(char **pp)
{
	char **m = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(m);
}

/**
 * _realloc - this function reallocates a block of memory in the heap
 * @ptr: this is a pointer to the previous malloc block
 * @old_size: this is the byte size of the prev block
 * @new_size: this is the byte size of the new block
 *
 * Return: pointer to the old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
