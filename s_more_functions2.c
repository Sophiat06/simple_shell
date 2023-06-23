#include "shell.h"

/**
 * _erratoi - This changes a string to an integer
 * @s: This the string to be changed
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int b = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (b = 0;  s[b] != '\0'; b++)
	{
		if (s[b] >= '0' && s[b] <= '9')
		{
			output *= 10;
			output += (s[b] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - This prints an error msg
 * @info: This is the variable & return info struct
 * @estr: The string containing specified error type
 * Return: 0 if no numbers in string,
 * converted number otherwise - 1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - This function prints a decimal (integer) number (base 10)
 * @input: This is the input
 * @fd: This is the filedescriptor to write to
 *
 * Return: This is the number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int b, sum_up = 0;
	unsigned int _ban_, now;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_ban_ = -input;
		__putchar('-');
		sum_up++;
	}
	else
		_ban_ = input;
	now = _ban_;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (_ban_ / b)
		{
			__putchar('0' + now / b);
			sum_up++;
		}
		now %= b;
	}
	__putchar('0' + now);
	sum_up++;

	return (sum_up);
}

/**
 * convert_number - This is a converter function, it converts it to string
 * @num: This is the number to be converted
 * @base: The base for conversion
 * @flags: The argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buff[50];
	char signal = 0;
	char *ptr;
	unsigned long b = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		b = -num;
		signal = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[b % base];
		b /= base;
	} while (b != 0);

	if (signal)
		*--ptr = signal;
	return (ptr);
}

/**
 * remove_comments - This function replaces first instance of '#' with '\0'
 * @buf: This is the address of the string to change
 *
 * Return: Always 0
 */
void remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}
