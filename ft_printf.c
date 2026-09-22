/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhshala <ayham.shalabi@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 21:45:21 by ayhshala          #+#    #+#             */
/*   Updated: 2026/09/22 14:59:35 by ayhshala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(char specifier, va_list args)
{
	if (specifier == 'c' || specifier == 's' || specifier == '%')
		return (ft_printf_char(specifier, args));
	if (specifier == 'd' || specifier == 'i' || specifier == 'u')
		return (ft_printf_nbr(specifier, args));
	if (specifier == 'x' || specifier == 'X' || specifier == 'p')
		return (ft_printf_hex(specifier, args));
	write(1, "%", 1);
	write(1, &specifier, 1);
	return (2);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			len += ft_format(format[++i], args);
		else if (format[i] != '%')
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
