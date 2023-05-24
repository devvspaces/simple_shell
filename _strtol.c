#include "main.h"

/**
 * _convert - convert a string
 * to long integer
 *
 * @nptr: string to convert
 * @endptr: string to place end
 * @base: integer base
 * @sign: number sign
 *
 * Return: new long value
 */
long _convert(const char *nptr, char **endptr, int base, int sign)
{
	long result = 0;
	int digit;

	while (*nptr != '\0')
	{
		if (*nptr >= '0' && *nptr <= '9')
			digit = *nptr - '0';
		else if (*nptr >= 'A' && *nptr <= 'Z')
			digit = *nptr - 'A' + 10;
		else if (*nptr >= 'a' && *nptr <= 'z')
			digit = *nptr - 'a' + 10;
		else
			break;
		if (digit >= base)
			break;
		if (sign == 1 && result > (LONG_MAX - digit) / base)
			errno = ERANGE;
		else if (sign == -1 && result < (LONG_MIN + digit) / base)
			errno = ERANGE;
		else
			result = result * base + digit;
		nptr++;
	}
	if (endptr != NULL)
		*endptr = (char *)nptr;
	return (result * sign);
}

/**
 * _strtol - convert a string
 * to long integer
 *
 * @nptr: string to convert
 * @endptr: string to place end
 * @base: integer base
 *
 * Return: new long value
 */
long _strtol(const char *nptr, char **endptr, int base)
{
	int sign = 1;

	while (*nptr == ' ' || *nptr == '\t')
		nptr++;

	if (*nptr == '-')
		sign = -1, nptr++;
	else if (*nptr == '+')
		nptr++;
	if (base == 0)
		if (*nptr == '0')
			if (nptr[1] == 'x' || nptr[1] == 'X')
				base = 16, nptr += 2;
			else
				base = 8, nptr++;
		else
			base = 10;
	else if (base == 16)
		if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			nptr += 2;
	return (_convert(nptr, endptr, base, sign));
}
