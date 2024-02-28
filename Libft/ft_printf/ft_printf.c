/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:01:38 by mott              #+#    #+#             */
/*   Updated: 2024/02/18 16:41:38 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		nbytes;
	va_list	ap;

	nbytes = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
			nbytes += ft_read_conversion(ap, &format);
		else
			nbytes += ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (nbytes);
}

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int	ft_putnstr(char *str, int n)
{
	int	nbytes;

	nbytes = 0;
	while (nbytes < n)
		ft_putchar(str[nbytes++]);
	return (nbytes);
}

int	ft_putnbr10(long n)
{
	int	nbytes;

	nbytes = 0;
	if (n >= 10)
		nbytes += ft_putnbr10(n / 10);
	nbytes += ft_putchar(n % 10 + '0');
	return (nbytes);
}

int	ft_putnbr16(unsigned long n, char xp)
{
	static const char	*base;
	int					nbytes;

	base = "0123456789abcdef";
	nbytes = 0;
	if (n >= 16)
		nbytes += ft_putnbr16(n / 16, xp);
	if (xp == 'x' || xp == 'p')
		nbytes += ft_putchar(base[n % 16]);
	else
		nbytes += ft_putchar(pf_toupper(base[n % 16]));
	return (nbytes);
}
