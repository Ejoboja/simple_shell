#include "shell.h"

/**
* interactive - Checks if the shell is in interactive mode
* @info: Pointer to the info_t struct
*
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_delim - Checks if a character is a delimiter
* @c: The character to check
* @delim: The delimiter string
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
* _isalpha - Checks for an alphabetic character
* @c: The character to check
* Return: 1 if c is alphabetic, 0 otherwise
*/
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0));
}

/**
* _atoi - Converts a string to an integer
* @s: The string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
	if (s[i] == '-')
	sign *= -1;

	if (s[i] >= '0' && s[i] <= '9')
	{
	flag = 1;
	result *= 10;
	result += (s[i] - '0');
	}
	else if (flag == 1)
	flag = 2;
	}

	Output = (sign == -1) ? -result : result;
	return (output);
}
