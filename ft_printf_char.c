#include "ft_printf.h"

/*Writes a single character to standard output and returns character count.*/
static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

/*Writes a string to standard output, outputting (null) if string pointer is NULL.*/
static int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

/*Handles character, string, and literal percent conversion specifiers.*/
int	ft_printf_char(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}
