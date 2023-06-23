#include "shell.h"

/**
 * bfree - This function releases a pointer and
 * checks if a pointer is valid and
 * not freed already. it frees the memory and sets
 * the pointer to Null to avoid dangling pointers
 *
 * @ptr: This is the address to the pointer
 *
 * Return: This returns 1 if freed otherwise 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
