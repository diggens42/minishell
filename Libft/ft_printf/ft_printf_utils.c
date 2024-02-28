/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:25:36 by mott              #+#    #+#             */
/*   Updated: 2024/02/18 16:40:45 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	pf_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

int	ft_strnlen(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		i++;
	return (i);
}

int	ft_nbrlen(unsigned long nbr, unsigned long base)
{
	int	nbrlen;

	nbrlen = 1;
	while (nbr >= base)
	{
		nbr /= base;
		nbrlen++;
	}
	return (nbrlen);
}

int	ft_fill(int n, char c)
{
	int	nbytes;

	nbytes = 0;
	while (n-- > 0)
		nbytes += ft_putchar(c);
	return (nbytes);
}
