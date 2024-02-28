/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:36:59 by mott              #+#    #+#             */
/*   Updated: 2023/11/02 15:08:05 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_process_char(int c, t_flags *flags)
{
	int	nbytes;

	nbytes = 0;
	if (flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width - sizeof(char), ' ');
	nbytes += ft_putchar(c);
	if (flags->left_adjusted == true)
		nbytes += ft_fill(flags->field_width - sizeof(char), ' ');
	return (nbytes);
}

int	ft_process_str(char *str, t_flags *flags)
{
	int		nbytes;
	size_t	strnlen;

	nbytes = 0;
	if (str == NULL)
		str = "(null)";
	strnlen = ft_strnlen(str, flags->precision);
	if (flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width - strnlen, ' ');
	nbytes += ft_putnstr(str, strnlen);
	if (flags->left_adjusted == true)
		nbytes += ft_fill(flags->field_width - strnlen, ' ');
	return (nbytes);
}

int	ft_process_nbr10(long nbr, t_flags *flags)
{
	int		nbytes;
	int		nbrlen;
	int		sign;
	bool	zero;

	nbytes = 0;
	zero = (nbr == 0 && flags->precision == 0);
	sign = ft_set_sign(&nbr, flags);
	nbrlen = ft_nbrlen(nbr, 10);
	if (flags->precision < nbrlen)
		flags->precision = nbrlen;
	if (zero == false)
		flags->field_width -= flags->precision;
	if (flags->zero_padded == false && flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width, ' ');
	if (sign != 0)
		nbytes += ft_putchar(sign);
	if (flags->zero_padded == true && flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width, '0');
	nbytes += ft_fill(flags->precision - nbrlen, '0');
	if (zero == false)
		nbytes += ft_putnbr10(nbr);
	if (flags->left_adjusted == true)
		nbytes += ft_fill(flags->field_width, ' ');
	return (nbytes);
}

int	ft_process_nbr16(long nbr, t_flags *flags, char xp)
{
	int	nbytes;
	int	nbrlen;

	nbytes = 0;
	if (nbr == 0 && flags->precision == 0)
		return (ft_fill(flags->field_width, ' '));
	if ((flags->alternate_form == true && nbr != 0) || xp == 'p')
		flags->field_width -= 2;
	nbrlen = ft_nbrlen(nbr, 16);
	if (flags->precision < nbrlen)
		flags->precision = nbrlen;
	flags->field_width -= flags->precision;
	if (flags->zero_padded == false && flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width, ' ');
	if ((flags->alternate_form == true && nbr != 0) && xp == 'X')
		nbytes += ft_putnstr("0X", 2);
	else if ((flags->alternate_form == true && nbr != 0) || xp == 'p')
		nbytes += ft_putnstr("0x", 2);
	if (flags->zero_padded == true && flags->left_adjusted == false)
		nbytes += ft_fill(flags->field_width, '0');
	nbytes += ft_fill(flags->precision - nbrlen, '0');
	nbytes += ft_putnbr16(nbr, xp);
	if (flags->left_adjusted == true)
		nbytes += ft_fill(flags->field_width, ' ');
	return (nbytes);
}

int	ft_set_sign(long *nbr, t_flags *flags)
{
	if (*nbr < 0)
	{
		*nbr = -(*nbr);
		flags->field_width--;
		return ('-');
	}
	else if (flags->plus_sign == true)
	{
		flags->field_width--;
		return ('+');
	}
	else if (flags->space_sign == true)
	{
		flags->field_width--;
		return (' ');
	}
	return (0);
}
