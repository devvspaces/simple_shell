#include "main.h"

/**
 * write_fd - writes buf to
 * file descriptor
 *
 * @fd: file descriptor
 * @buf: buffer to write
 *
 * Return: number of bytes writen on success
 * else -1
 */
int write_fd(int fd, const char *buf)
{
	ssize_t written;
	size_t len = _strlen(buf);

	written = write(fd, buf, len);
	if (written == -1 || written < (ssize_t)len)
	{
		perror("Write failed");
		return (-1);
	}
	return (written);
}

/**
 * write_stdout - writes buf stdout
 *
 * @buf: buffer to write
 *
 * Return: number of bytes writen on success
 * else -1
 */
int write_stdout(const char *buf)
{
	return (write_fd(STDOUT_FILENO, buf));
}

/**
 * write_stderr - writes buf stderr
 *
 * @buf: buffer to write
 *
 * Return: number of bytes writen on success
 * else -1
 */
int write_stderr(const char *buf)
{
	return (write_fd(STDERR_FILENO, buf));
}
