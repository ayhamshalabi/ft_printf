#include "ft_printf.h"

/*Recursively writes a signed decimal integer to standard output.*/
static int	ft_putnbr(int n)
{
	char	c;
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}

/*Recursively writes an unsigned decimal integer to standard output.*/
static int	ft_putunsigned(unsigned int n)
{
	char	c;
	int		len;

	len = 0;
	if (n >= 10)
		len += ft_putunsigned(n / 10);
	c = (n % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}

/*Handles signed and unsigned decimal numeric conversion specifiers.*/
int	ft_printf_nbr(char specifier, va_list args)
{
	if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (specifier == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	return (0);
}
