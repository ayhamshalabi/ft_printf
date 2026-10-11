#include "ft_printf.h"

/*Recursively converts and writes an unsigned number in base 16 lowercase or uppercase.*/
static int	ft_puthex(char specifier, unsigned long n)
{
	char	*base;
	int		len;

	if (specifier == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
		len += ft_puthex(specifier, n / 16);
	len += write(1, &base[n % 16], 1);
	return (len);
}

/*Outputs a void pointer memory address in lowercase hex prefixed with 0x.*/
static int	ft_putptr(void *ptr)
{
	unsigned long	addr;
	int				len;

	if (!ptr)
		return (write(1, "(nil)", 5));
	len = write(1, "0x", 2);
	addr = (unsigned long)ptr;
	len += ft_puthex('x', addr);
	return (len);
}

/*Handles hexadecimal and pointer address conversion specifiers.*/
int	ft_printf_hex(char specifier, va_list args)
{
	if (specifier == 'x' || specifier == 'X')
		return (ft_puthex(specifier, va_arg(args, unsigned int)));
	if (specifier == 'p')
		return (ft_putptr(va_arg(args, void *)));
	return (0);
}
