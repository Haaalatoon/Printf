/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhilane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:40:12 by hrhilane          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:14 by hrhilane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	handle_cors(va_list args, char id)
{
	char	*s;

	if (id == 'c')
	{
		ft_putchar_fd((char)va_arg(args, int), 1);
		return (1);
	}
	else if (id == 's')
	{
		s = va_arg(args, char *);
		if (s == NULL)
			return (write(1, "(null)", 6));
		else
		{
			ft_putstr_fd(s, 1);
			return (ft_strlen(s));
		}
	}
}

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		++len;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

static int	write_number(unsigned long long nb, char iden, int base, int prefix)
{
	char	c[16];
	short	i;
	int		count;

	i = 0;
	if (prefix)
		count = write(1, "0x", 2);
	else
		count = 0;
	if (nb == 0)
		return (count + write(1, "0", 1));
	while (nb)
	{
		if (nb % base < 10)
			c[i++] = nb % base + '0';
		else
			c[i++] = 'a' - ('x' - iden) + nb % base - 10;
		nb /= base;
	}
	count += i;
	while (i)
		write(1, &c[--i], 1);
	return (count);
}

int	handle_format(va_list args, char format)
{
	int				printed_chars;
	int				d;
	unsigned int	num;
	void			*addr;

	printed_chars = 0;
	if (format == 'd' || format == 'i')
	{
		d = va_arg(args, int);
		ft_putnbr_fd(d, 1);
		return (num_len(d));
	}
	if (format == 'u')
	{
		num = va_arg(args, unsigned int);
		printed_chars += write_number(num, 0, 10, 0);
	}
	else if (format == 'x' || format == 'X')
	{
		num = va_arg(args, unsigned int);
		printed_chars += write_number(num, format, 16, 0);
	}
	else if (format == 'p')
	{
		addr = va_arg(args, void *);
		if (addr == NULL)
			printed_chars += write(1, "(nil)", 5);
		else
			printed_chars += write_number((unsigned long long)addr, 'x', 16, 1);
	}
	return (printed_chars);
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
				handle_format(args, *format);
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

/*int	main(void)
{
	int		a;
	float	x;
	int		*ptr1;
	float	*ptr2;
	void	*p;

	// Character Tests
	printf("%%c Tests:\n");
	printf("Standard: |%c|\n", 'A');
	ft_printf("Custom:   |%c|\n", 'A');
	// String Tests
	printf("%%s Tests:\n");
	printf("Standard: |%s|\n", "Hello");
	ft_printf("Custom:   |%s|\n", "Hello");
	printf("Standard: |%s|\n", NULL);
	ft_printf("Custom:   |%s|\n", NULL);
	// Integer Tests
	printf("%%d/%%i Tests:\n");
	printf("Standard: %d %d %d\n", 0, -42, ULLONG_MAX);
	ft_printf("Custom:   %d %d %d\n", 0, -42, ULLONG_MAX);
	printf("Standard: %d\n", INT_MIN);
	ft_printf("Custom:   %d\n", INT_MIN);
	// Unsigned Tests
	printf("%%u Tests:\n");
	printf("Standard: %u %u %u\n", 0, 42, UINT_MAX);
	ft_printf("Custom:   %u %u %u\n", 0, 42, UINT_MAX);
	printf("Standard: %u\n", LONG_MIN);
	ft_printf("Custom:   %u\n", LONG_MIN);
	printf("Standard: %u\n", LLONG_MIN);
	ft_printf("Custom:   %u\n", LLONG_MIN);
	printf("Standard: %u\n", ULONG_MAX);
	ft_printf("Custom:   %u\n", ULONG_MAX);
	printf("%X\n", 202425);
	ft_printf("%X\n", 202425);
	printf("%X\n", 369852147);
	ft_printf("%X\n", 369852147);
	a = 43;
	x = 2.00;
	ptr1 = &a;
	ptr2 = &x;
	p = &a;
	printf("Standard: %p %p %p\n", ptr1, ptr2, p);
	ft_printf("Custom:   %p %p %p\n", ptr1, ptr2, p);
	printf("Standard: %p\n", NULL);
	ft_printf("Custom:   %p\n", NULL);
	printf("Standard: %d %u %x %p\n", INT_MIN, ULONG_MAX, LLONG_MIN, NULL);
	ft_printf("Custom:   %d %u %x %p\n", INT_MIN, ULONG_MAX, LLONG_MIN, NULL);
	printf("%%\n");
	ft_printf("%%\n");
	printf("%p\n", NULL);
	ft_printf("%p\n", NULL);
	return (0);
}
*/