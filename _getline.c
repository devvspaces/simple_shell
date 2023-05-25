
#include "main.h"

#define BUFFERSIZE 1

/**
 * _getline - Implementation of C getline function
 * that uses O(n) time complexity.
 *
 * Description: works
 *
 * @lineptr: pointer to buffer to populate
 * @n: pointer to size of buffer
 * @fd: file descriptor
 *
 * Return: total number of bytes written to
 * lineptr buffer
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	size_t n_read, cur = 0;
	static char buf[BUFFERSIZE];

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = 120;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
		{
			free(*lineptr);
			return (-1);
		}
	}

	while (1)
	{
		n_read = read(fd, buf, sizeof(char) * BUFFERSIZE);

		if (n_read <= 0)
			return (-1);

		_memcpy(*lineptr + cur, buf, n_read);
		cur += n_read;

		if (*buf == '\n')
			break;

		if (cur == *n)
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n + 2);
		}
	}

	*n = cur;
	*(*lineptr + cur) = '\0';
	return (cur);
}
