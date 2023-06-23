#include "shell.h"
/**
 * **strtow - This function splits a string into chars
 * and delimiters are ignored
 * @str: This is the input string
 * @d: This is the delimeter of the string
 * Return: the pointer to an array of strings, or NULL
 */
char **strtow(char *str, char *d)
{
	int a, b, c, z, num_count = 0;
	char **q;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			num_count++;

	if (num_count == 0)
		return (NULL);
	q = malloc((1 + num_count) * sizeof(char *));
	if (!q)
		return (NULL);
	for (a = 0, b = 0; b < num_count; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		q[b] = malloc((c + 1) * sizeof(char));
		if (!q[b])
		{
			for (c = 0; c < b; c++)
				free(q[c]);
			free(q);
			return (NULL);
		}
		for (z = 0; z < c; z++)
			q[b][z] = str[a++];
		q[b][z] = 0;
	}
	q[b] = NULL;
	return (q);
}

/**
 * **strtow2 - This function splits a string into characters
 * @str: This is the string
 * @d: This is the input delimeter
 * Return: The pointer to an array of strings
 */
char **strtow2(char *str, char d)
{
	int a, b, c, z, num_count = 0;
	char **q;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			num_count++;
	if (num_count == 0)
		return (NULL);
	q = malloc((1 + num_count) * sizeof(char *));
	if (!q)
		return (NULL);
	for (a = 0, b = 0; b < num_count; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		q[b] = malloc((c + 1) * sizeof(char));
		if (!q[b])
		{
			for (c = 0; c < b; c++)
				free(q[c]);
			free(q);
			return (NULL);
		}
		for (z = 0; z < c; z++)
			q[b][z] = str[a++];
		q[b][z] = 0;
	}
	q[b] = NULL;
	return (q);
}
