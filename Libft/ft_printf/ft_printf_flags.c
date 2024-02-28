/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:03:21 by mott              #+#    #+#             */
/*   Updated: 2023/11/02 14:53:24 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_read_conversion(va_list ap, const char **format)
{
	t_flags	flags;

	flags = ft_init_flags(ap, format);
	if (**format == 'c')
		return (ft_process_char(va_arg(ap, int), &flags));
	else if (**format == 's')
		return (ft_process_str(va_arg(ap, char *), &flags));
	else if (**format == 'd' || **format == 'i')
		return (ft_process_nbr10(va_arg(ap, int), &flags));
	else if (**format == 'u')
		return (ft_process_nbr10(va_arg(ap, unsigned int), &flags));
	else if (**format == 'x' || **format == 'X')
		return (ft_process_nbr16(va_arg(ap, unsigned int), &flags, **format));
	else if (**format == 'p')
		return (ft_process_nbr16(va_arg(ap, unsigned long), &flags, **format));
	else if (**format == '%')
		return (ft_process_char('%', &flags));
	return (0);
}

t_flags	ft_init_flags(va_list ap, const char **format)
{
	t_flags	flags;

	flags.left_adjusted = false;
	flags.plus_sign = false;
	flags.space_sign = false;
	flags.alternate_form = false;
	flags.zero_padded = false;
	flags.field_width = -1;
	flags.precision = -1;
	flags = ft_read_flags(format, &flags);
	flags = ft_read_width(ap, format, &flags);
	flags = ft_read_precision(ap, format, &flags);
	if (flags.left_adjusted == true || flags.precision != -1)
		flags.zero_padded = false;
	return (flags);
}

t_flags	ft_read_flags(const char **format, t_flags *flags)
{
	while (**format != '\0')
	{
		(*format)++;
		if (**format == '-')
			flags->left_adjusted = true;
		else if (**format == '+')
			flags->plus_sign = true;
		else if (**format == ' ')
			flags->space_sign = true;
		else if (**format == '#')
			flags->alternate_form = true;
		else if (**format == '0')
			flags->zero_padded = true;
		else
			break ;
	}
	return (*flags);
}

t_flags	ft_read_width(va_list ap, const char **format, t_flags *flags)
{
	if (ft_is_digit(**format) == true)
	{
		flags->field_width = 0;
		while (ft_is_digit(**format) == true)
		{
			flags->field_width = flags->field_width * 10 + **format - '0';
			(*format)++;
		}
	}
	else if (**format == '*')
	{
		flags->field_width = va_arg(ap, int);
		if (flags->field_width < 0)
		{
			flags->field_width = -flags->field_width;
			flags->left_adjusted = true;
		}
		(*format)++;
	}
	return (*flags);
}

t_flags	ft_read_precision(va_list ap, const char **format, t_flags *flags)
{
	if (**format != '.')
		return (*flags);
	(*format)++;
	flags->precision = 0;
	if (ft_is_digit(**format) == true)
	{
		while (ft_is_digit(**format) == true)
		{
			flags->precision = flags->precision * 10 + **format - '0';
			(*format)++;
		}
	}
	else if (**format == '*')
	{
		flags->precision = va_arg(ap, int);
		if (flags->precision < 0)
			flags->precision = 0;
		(*format)++;
	}
	return (*flags);
}
