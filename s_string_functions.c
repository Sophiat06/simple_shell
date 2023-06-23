#include "shell.h"

/**
 * _strlen - This func returns the length of a string
 * @s: This is the string wich length is to be check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int n = 0;

	if (!s)
		return (0);

	while (*s++)
		n++;
	return (n);
}

/**
 * _strcmp - This func performs etymological comparison
 * of two strings.
 * @s1: This is the first string
 * @s2: This the second string
 *
 * Return: This returns negative if s1 < s2, and
 * positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - This func checks if needle starts with haystack
 * @haystack: This is the string used to search
 * @needle: This isthe substring used to find
 *
 * Return: This returns address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This func concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 *
 * Return: This returns a pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ban = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ban);
}
