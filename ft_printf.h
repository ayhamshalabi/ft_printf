#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_printf_char(char specifier, va_list args);
int	ft_printf_nbr(char specifier, va_list args);
int	ft_printf_hex(char specifier, va_list args);

#endif