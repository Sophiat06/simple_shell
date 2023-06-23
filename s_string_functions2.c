#include "shell.h"
/**
 * _strcpy - this function duplicates a string
 * @dest: this is the file destination
 * @src: this is the source destination of the file
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int s = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[s])
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
	return (dest);
}

/**
 * _strdup - This function copies a string
 * @str: this is the string to be copied
 *
 * Return: the pointer to the copied string
 */
char *_strdup(const char *str)
{
	int span = 0;
	char *ban;

	if (str == NULL)
		return (NULL);
	while (*str++)
		span++;
	ban = malloc(sizeof(char) * (span + 1));
	if (!ban)
		return (NULL);
	for (span++; span--;)
		ban[span] = *--str;
	return (ban);
}

/**
 *_puts - This function prints an input string
 *@str: This is the string to be printed
 *
 * Return: Null
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: This is the character to be printed
 *
 * Return: On success 1
 * On error, -1 is returned
 */
int _putchar(char c)
{
	static int q;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(1, buffer, q);
		q = 0;
	}
	if (c != BUF_FLUSH)
		buffer[q++] = c;
	return (1);
}
