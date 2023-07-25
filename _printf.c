#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function code
 * @format: Contains string to be printed in specified format.
 *
 *
 * Return: Number of characters that has been printed.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			size = get_size(format, &i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer.
 * @buf: Array of chars to be printed
 * @buff_ind: Index at which to add next char,
 *		represents the length of the buffer.
 */
void print_buffer(char buf[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buf[0], *buff_ind);

	*buff_ind = 0;
}
