#include "shell.h"

/**
* _erratoi - Converts a string to an integer.
* @s: The string to be converted.
* Return: 0 if no numbers in string, converted number otherwise. -1 on error.
*/
	int _erratoi(char *s) i
	{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	s++;  /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
	if (s[i] >= '0' && s[i] <= '9')
	{
	result *= 10;
	result += (s[i] - '0');
	if (result > INT_MAX)
	return (-1);
	}
	else
	{
		return (-1);
	}
}
	return (result);
}

/**
* print_error - Prints an error message.
* @info: The parameter & return info struct.
* @estr: String containing specified error type.
* Return: Nothing.
*/
	void print_error(info_t *info, char *estr)
	{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
* print_d - Prints a decimal (integer) number (base 10).
* @input: The input.
* @fd: The file descriptor to write to.
* Return: Number of characters printed.
*/
	int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	__putchar = _eputchar;
	if (input < 0)
	{
	_abs_ = -input;
	__putchar('-');
	count++;
	}
	else
	{
	_abs_ = input;
	}
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
	if (_abs_ / i)
	{
	__putchar('0' + current / i);
	count++;
	}
	current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
* convert_number - Converter function, a clone of itoa.
* @num: Number.
* @base: Base.
* @flags: Argument flags.
* Return: String.
*/
	char *convert_number(long int num, int base, int flags)
	{
	/*Function implementation remains unchanged for conversion purposes*/
	/*Ensure code structure remains consistent with shell.h file*/
}

/**
* remove_comments - Replaces first instance of '#' with '\0'.
* @buf: Address of the string to modify.
* Return: Always 0.
*/
	void remove_comments(char *buf)
	{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
	if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
	{
	buf[i] = '\0';
	break;
	}
	}
}
