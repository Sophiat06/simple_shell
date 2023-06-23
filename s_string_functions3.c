#include "shell.h"
#include "stddef.h"
/**
 **_strncpy - Yjis function copies a string
 *@dest: This is the destination where the string is to be copied to
 *@src: This is the source dest string
 *@n: This is the amount of characters to be copied
 *Return: This concatenate the string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, m;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		m = a;
		while (m < n)
		{
			dest[m] = '\0';
			m++;
		}
	}
	return (s);
}

/**
 **_strncat - This func is used to concatenates two strings
 *@dest: This is the first string
 *@src: This is the second string
 *@n: This is maximum amount of bytes to be used
 *Return: This returns the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, m;
	char *s = dest;

	a = 0;
	m = 0;
	while (dest[a] != '\0')
		a++;
	while (src[m] != '\0' && m < n)
	{
		dest[a] = src[m];
		a++;
		m++;
	}7
	if (m < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - This func locates a character in a string
 *@s: This is the string to be parsed
 *@c: This is the character to look for
 *Return: This returns (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
