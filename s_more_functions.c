#include "shell.h"
/**
 * interactive - this function returns true if shell is in the interactive mode
 * @info: this is the struct address used
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - this function checks if a character is a delimeter or not
 * @c: this is the character to be checked
 * @delim: this is the delimeter string to be used
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - this function checks for alphabetic char
 *@c: this is the char to input
 *Return: 1 if c is an alphabet, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - this function changes a string to an integer
 *@s: this is the string to be changed
 *Return: 0 if no numbers in the string
 */

int _atoi(char *s)
{
	int a, input = 1, flab = 0, output;
	unsigned int data = 0;

	for (a = 0;  s[a] != '\0' && flab != 2; a++)
	{
		if (s[a] == '-')
			input *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flab = 1;
			data *= 10;
			data += (s[a] - '0');
		}
		else if (flab == 1)
			flab = 2;
	}

	if (input == -1)
		output = -data;
	else
		output = data;

	return (output);
}
