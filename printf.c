#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		ft_putchar(*s++);
}

static int num_len(int n)
{
	int len;

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

static int	to_unsigned(long long n)
{
	unsigned int nb;
	char	c[10];
	short	i;
	int count;

	i = 0;
	nb = (unsigned int)n;
	 if (nb == 0)
    {
        write(1, "0", 1);
        return (1);
    }
	while (nb)
	{
		c[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	count = i;
	while (i)
		write(1, &c[--i], 1);
	return (count);
}

static int	to_hex(long long n)
{
	unsigned int nb;
	char	c[8];
	short	i;
	int count;

	i = 0;
	nb = (unsigned int)n;
	 if (nb == 0)
    {
        write(1, "0", 1);
        return (1);
    }
	while (nb)
	{
		if (nb % 16 < 10)
			c[i++] = nb % 16 + 48;
		else
			c[i++] = 'a' + nb % 16 - 10;
		nb /= 16;
	}
	count = i;
	while (i)
		write(1, &c[--i], 1);
	return (count);
}

static int	to_address(long long n)
{
	unsigned long nb;
	char	c[16];
	short	i;
	int count;

	i = 0;
	nb = (unsigned long)n;
	write(1, "0x", 2);
	while (nb)
	{
		if (nb % 16 < 10)
			c[i++] = nb % 16 + 48;
		else
			c[i++] = 'a' + nb % 16 - 10;
		nb /= 16;
	}
	count = i + 2;
	while (i)
		write(1, &c[--i], 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 'c')
		{
			char c;

			c = va_arg(args, int);
			ft_putchar(c);
			printed_chars++;
			format += 2;
			continue ;
		}
		else if (*format == '%' && *(format + 1) == 's')
		{
			char *s;

			s = va_arg(args, char *);
			if (s == NULL)
    		{
        		write(1, "(null)", 6);
        		printed_chars += 6;
    		}
			else
			{
				ft_putstr(s);
				printed_chars += ft_strlen(s);
			}
			format += 2;
			continue;
		}
		else if (*format == '%' && (*(format + 1) == 'd' || *(format + 1) == 'i'))
		{
			int d;

			d = va_arg(args, int);
			ft_putnbr_fd(d, 1);
			printed_chars += num_len(d);
			format +=2;
			continue;
		}
		else if (*format == '%' && *(format + 1) == 'u')
		{
			long long u;

			u = va_arg(args, long long);
			printed_chars += to_unsigned(u);
			format += 2;
			continue;
		}
		else if (*format == '%' && *(format + 1) == 'x')
		{
			long long hx;

			hx = va_arg(args, long long);
			printed_chars += to_hex(hx);
			format += 2;
			continue;
		}
		else if (*format == '%' && *(format + 1) == 'p')
		{
			long long addr;

			addr = va_arg(args, long long);
			if (addr == 0)
			{
				write(1, "(nil)", 5);
        		printed_chars += 5;
			}
			else
				printed_chars += to_address(addr);			
			format += 2;
			continue;
		}
		else
		{
			ft_putchar(*format);
			printed_chars++;
			format++;
		}
	}
	va_end(args);
	return (printed_chars);
}

int main() {
    // Character Tests
    /*printf("%%c Tests:\n");
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

	printf("%x\n", LLONG_MIN);
	ft_printf("%x\n", LLONG_MIN);*/

	 int x = 42;
    int *ptr = 0;

    printf("Standard: %p\n", ptr);
    ft_printf("Custom:   %p\n", ptr);

    printf("Standard: %p\n", NULL);
    ft_printf("Custom:   %p\n", NULL);
    return 0;
}