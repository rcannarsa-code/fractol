/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcannars <rcannars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:02:51 by rcannars          #+#    #+#             */
/*   Updated: 2025/02/23 13:59:13 by rcannars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* static int	formatter(va_list arguments, const char format)
{
	int	length_print;

	length_print = 0;
	if (format == 'c')
		length_print += ft_putchar(va_arg(arguments, int));
	else if (format == 's')
		length_print += ft_putstr(va_arg(arguments, char *));
	else if (format == 'p')
		length_print += ft_print_ptr(va_arg(arguments, unsigned long));
	else if (format == 'd' || format == 'i')
		length_print += ft_putnbr(va_arg(arguments, int));
	else if (format == 'u')
		length_print += ft_print_unsigned(va_arg(arguments, unsigned int));
	else if (format == 'x' || format == 'X')
		length_print += ft_print_hex(va_arg(arguments, unsigned int),
				format == 'X');
	else if (format == '%')
		length_print += ft_putchar('%');
	return (length_print);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		length_print;
	int		i;
	int		chars_written;
	int		chars_written;

	length_print = 0;
	i = 0;
	va_start(arguments, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length_print += formatter(arguments, format[i + 1]);
			i++;
		}
		else
			length_print += ft_putchar(format[i]);
		i++;
	}
	va_end(arguments);
	return (length_print);
} */
static int	handle_format(va_list args, char specifier)
{
	chars_written = 0;
	if (specifier == 'c')
		chars_written += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		chars_written += ft_putstr(va_arg(args, char *));
	else if (specifier == 'p')
		chars_written += ft_print_ptr(va_arg(args, unsigned long));
	else if (specifier == 'd' || specifier == 'i')
		chars_written += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		chars_written += ft_print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		chars_written += ft_print_hex(va_arg(args, unsigned int),
				specifier == 'X');
	else if (specifier == '%')
		chars_written += ft_putchar('%');
	return (chars_written);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg_list;
	int		total_chars;
	int		pos;

	total_chars = 0;
	pos = 0;
	va_start(arg_list, str);
	while (str[pos])
	{
		if (str[pos] == '%')
		{
			total_chars += handle_format(arg_list, str[pos + 1]);
			pos++;
		}
		else
		{
			total_chars += ft_putchar(str[pos]);
		}
		pos++;
	}
	va_end(arg_list);
	return (total_chars);
}
