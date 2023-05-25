#include "main.h"

/**
 * r_memset - copy values of ptr to mem
 * up until min
 *
 * @mem: new memory address (dest)
 * @ptr: old memory address (src)
 * @min: min number of copy
 */
void r_memset(char *mem, char *ptr, int min)
{
	for (; min > 0; min--)
	{
		*mem = *ptr;
		mem++;
		ptr++;
	}
}

/**
 * _realloc - reallocates a memory block
 * using malloc and free
 *
 * @ptr: pointer for old address
 * @old_size: old size of memory address ptr
 * @new_size: new size to be reallocated
 *
 * Return: newly allocated memory address if
 * successfull
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int min = old_size;
	char *mem;

	if (ptr == NULL)
		return (malloc(new_size));

	if (old_size == new_size)
		return (ptr);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size < min)
		min = new_size;

	mem = malloc(new_size);
	if (mem == NULL)
	{
		free(mem);
		return (NULL);
	}

	r_memset(mem, ptr, min);
	free(ptr);
	return (mem);
}
