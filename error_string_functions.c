#include "shell.h"

/**
 *_eputs -This prints an input string
 * @str: This is the string to be printed
 *
 * Return: This returns nothing
 */
void _eputs(char *str)
{
	int q = 0;

	if (!str)
		return;
	while (str[q] != '\0')
	{
		_eputchar(str[q]);
		q++;
	}
}

/**
 * _eputchar -This function writes the character c to stderr
 * @c: This the character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int q;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(2, buf, q);
		q = 0;
	}
	if (c != BUF_FLUSH)
		buf[q++] = c;
	return (1);
}

/**
 * _putfd - This func writes the character c to given fd
 * @c: This is the character to print
 * @fd: This is the file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int q;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || q >= WRITE_BUF_SIZE)
	{
		write(fd, buf, q);
		q = 0;
	}
	if (c != BUF_FLUSH)
		buf[q++] = c;
	return (1);
}

/**
 *_putsfd -This prints an input string
 * @str: This is the string to be printed
 * @fd: This is the filedescriptor to write to
 *
 * Return: This returns the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int q = 0;

	if (!str)
		return (0);
	while (*str)
	{
		q += _putfd(*str++, fd);
	}
	return (q);
}
