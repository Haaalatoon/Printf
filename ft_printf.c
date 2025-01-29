/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:12 by hrhilane          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:14 by hrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *str)
{
	const char	*s;

	s = str;
	while (*s != '\0')
		s++;
	return (s - str);
}

static int	handle_cors(va_list args, char id)
{
	char	c;
	char	*s;

	if (id == 'c')
	{
		c = (char)va_arg(args, int);
		return (write(1, &c, 1));
	}
	else if (id == 's')
	{
		s = va_arg(args, char *);
		if (s == NULL)
			return (write(1, "(null)", 6));
		return (write(1, s, ft_strlen(s)));
	}
	return (0);
}

static int	write_number(long long nb, char iden, int base)
{
	char				buffer[32];
	int					*counter;
	unsigned long long	unb;

	counter = (int [2]){0, 0};
	unb = nb;
	if (base == 10 && nb < 0)
	{
		counter[0] += write(1, "-", 1);
		unb = -nb;
	}
	if (unb == 0)
		return (write(1, "0", 1));
	while (unb)
	{
		if (unb % base < 10)
			buffer[counter[1]++] = unb % base + '0';
		else
			buffer[counter[1]++] = 'a' - ('x' - iden) + unb % base - 10;
		unb /= base;
	}
	while (counter[1])
		counter[0] += write(1, &buffer[--counter[1]], 1);
	return (counter[0]);
}

static int	handle_dixup(va_list args, char format)
{
	int				d;
	unsigned int	num;
	void			*addr;

	if (format == 'd' || format == 'i')
		return (d = va_arg(args, int), write_number(d, 0, 10));
	if (format == 'u')
		return (num = va_arg(args, unsigned int), write_number(num, 0, 10));
	else if (format == 'x' || format == 'X')
		return (num = va_arg(args, unsigned int),
			write_number(num, format, 16));
	else if (format == 'p')
	{
		addr = va_arg(args, void *);
		if (addr == NULL)
			return (write(1, "(nil)", 5));
		else
			return (write(1, "0x", 2)
				+ write_number((unsigned long long)addr, 'x', 16));
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c' || *format == 's')
				printed_chars += handle_cors(args, *format);
			else if (*format == 'd' || *format == 'i' || *format == 'x'
				|| *format == 'X' || *format == 'u' || *format == 'p')
				printed_chars += handle_dixup(args, *format);
			else if (*format == '%')
				printed_chars += write(1, "%", 1);
			format++;
		}
		else
			printed_chars += write(1, format++, 1);
	}
	va_end(args);
	return (printed_chars);
}
