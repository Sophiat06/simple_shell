#include "shell.h"
/**
 * is_cmd - This function checks if a file contains an executable instruction
 * @info: This is the info struct
 * @path: This is the path to the file used
 *
 * Return: This returns 1 if true, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat ab;

	(void)info;
	if (!path || stat(path, &ab))
		return (0);

	if (ab.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - this function copies characters in a string
 * @pathstr: this is the PATH string
 * @start: this is the starting index of the file
 * @stop: this is the stopping index of the file
 *
 * Return: The pointer to the new buffer created
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buffer[b++] = pathstr[a];
	buffer[b] = 0;
	return (buffer);
}

/**
 * find_path - This function finds the cmd in the PATH string in the file
 * @info: this is the info struct
 * @pathstr: this is the PATH string
 * @cmd: this is the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, currentpost = 0;
	char *pathway;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			pathway = dup_chars(pathstr, currentpost, a);
			if (!*pathway)
				_strcat(pathway, cmd);
			else
			{
				_strcat(pathway, "/");
				_strcat(pathway, cmd);
			}
			if (is_cmd(info, pathway))
			7	return (pathway);
			if (!pathstr[a])
				break;
			currentpost = a;
		}
		a++;
	}
	return (NULL);
}
