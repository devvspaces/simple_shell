#include "main.h"

/**
 * _strcpy - copies a string from one pointer to another
 *	including the terminating null byte (\0)
 *
 * @src: source of string parameter input
 * @dest: destination of string
 *
 * Return: pointer to dest input parameter
 */

char *_strcpy(char *dest, char *src)
{
	int a, b = 0;

	for (a = 0; src[a] != '\0'; ++a)
	{
		dest[b] = src[a];
		++b;
	}
	dest[b] = '\0';

	return (dest);
}

/**
 * _strncpy - copies n bytes of string from one
 * pointer to another
 *
 * @src: source of string parameter input
 * @dest: destination of string
 * @n: amount of bytes to copy
 *
 * Return: pointer to dest input parameter
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int a, b;

	for (a = 0, b = 0; src[a] != '\0' && a < n; ++a, ++b)
		dest[b] = src[a];
	return (dest);
}

/**
 * _strstr - returns a pointer to the
 * first occurrence of needle in the haystack
 *
 * @haystack: source of string parameter input
 * @needle: string to search for
 *
 * Return: pointer to dest input parameter
 */
char *_strstr(char *haystack, const char *needle)
{
	char *ptr = haystack;
	size_t nlen = strlen(needle);

	for (; *ptr != '\0'; ptr++)
		if (strncmp(ptr, needle, nlen) == 0)
			return (ptr);
	return (NULL);
}

/**
 * replace - replaces every occurence of
 * tok in str with replacement.
 *
 * @str: source of string parameter input
 * @tok: what to be replaced
 * @replacement: replacement string
 *
 * Return: pointer to the new str
 */
char *replace(char *str, const char *tok, const char *replacement)
{
	int tokLen = _strlen(tok);
	int replacementLen = _strlen(replacement);
	int diff = replacementLen - tokLen;
	int count = 0, newLen, len;
	char *pos, *dest, *src, *newStr;

	pos = _strstr(str, tok);
	while (pos != NULL)
		count++, pos = _strstr(pos + tokLen, tok);

	newLen = _strlen(str) + count * diff;

	newStr = malloc(newLen + 1);
	if (newStr == NULL)
		return (free(newStr), NULL);

	dest = newStr;
	src = str;
	while ((pos = _strstr(src, tok)) != NULL)
	{
		len = pos - src;
		_strncpy(dest, src, len);
		dest += len;
		src += len + tokLen;
		_strncpy(dest, replacement, replacementLen);
		dest += replacementLen;
	}
	_strcpy(dest, src);

	return (newStr);
}
