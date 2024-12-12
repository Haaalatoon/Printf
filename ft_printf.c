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
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		else
		{
			ft_putstr(s);
			return (ft_strlen(s));
		}
	}
	return (0);
}

static int	write_number(long long nb, char iden, int base)
{
	char				c[32];
	int					*i;
	unsigned long long	unb;

	i = (int [2]){0, 0};
	unb = nb;
	if (base == 10 && nb < 0)
	{
		i[0] += write(1, "-", 1);
		unb = -nb;
	}
	if (unb == 0)
		return (i[0] + write(1, "0", 1));
	while (unb)
	{
		if (unb % base < 10)
			c[i[1]++] = unb % base + '0';
		else
			c[i[1]++] = 'a' - ('x' - iden) + unb % base - 10;
		unb /= base;
	}
	while (i[1])
		i[0] += write(1, &c[--i[1]], 1);
	return (i[0]);
}

static int	handle_dicxup(va_list args, char format)
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
		{
			write(1, "0x", 2);
			return (2 + write_number((unsigned long long)addr, 'x', 16));
		}
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
				printed_chars += handle_dicxup(args, *format);
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
	printf(" %p \n", -1);
	ft_printf(" %p \n", -1);
	return 0;
}

int main(){
    // Character tests
    printf("--- Character Tests ---\n");
    int ft_ret = ft_printf("Char test: %c\n", 'A');
    int std_ret = printf("Char test: %c\n", 'A');
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // String tests
    printf("\n--- String Tests ---\n");
    ft_ret = ft_printf("String test: %s\n", "Hello, World!");
    std_ret = printf("String test: %s\n", "Hello, World!");
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Null string test
    printf("\n--- Null String Test ---\n");
    ft_ret = ft_printf("Null string: %s\n", NULL);
    std_ret = printf("Null string: %s\n", NULL);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Integer tests
    printf("\n--- Integer Tests ---\n");
    ft_ret = ft_printf("Decimal: %d, Integer: %i\n", 42, -17);
    std_ret = printf("Decimal: %d, Integer: %i\n", 42, -17);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Extreme integer tests
    printf("\n--- Extreme Integer Tests ---\n");
    ft_ret = ft_printf("INT_MIN: %d, INT_MAX: %d\n", INT_MIN, INT_MAX);
    std_ret = printf("INT_MIN: %d, INT_MAX: %d\n", INT_MIN, INT_MAX);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Unsigned integer tests
    printf("\n--- Unsigned Integer Tests ---\n");
    ft_ret = ft_printf("Unsigned: %u\n", 4294967295U);
    std_ret = printf("Unsigned: %u\n", 4294967295U);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Hexadecimal tests
    printf("\n--- Hexadecimal Tests ---\n");
    ft_ret = ft_printf("Lowercase hex: %x, Uppercase hex: %X\n", 255, 255);
    std_ret = printf("Lowercase hex: %x, Uppercase hex: %X\n", 255, 255);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Pointer tests
    printf("\n--- Pointer Tests ---\n");
    int x = 42;
    ft_ret = ft_printf("Pointer: %p\n", (void*)&x);
    std_ret = printf("Pointer: %p\n", (void*)&x);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Null pointer testn
    printf("\n--- Null Pointer Test ---\n");
    ft_ret = ft_printf("Null pointer: %p\n", NULL);
    std_ret = printf("Null pointer: %p\n", NULL);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    // Mixed format test
    printf("\n--- Mixed Format Test ---\n");
    ft_ret = ft_printf("Mixed: %c %s %d %x %p %%\n", 'A',
				"Hello", 42, 255, (void*)&x);
    std_ret = printf("Mixed: %c %s %d %x %p %%\n", 'A',
				"Hello", 42, 255, (void*)&x);
    printf("ft_printf return: %d, printf return: %d\n", ft_ret, std_ret);

    return 0;
}*/
