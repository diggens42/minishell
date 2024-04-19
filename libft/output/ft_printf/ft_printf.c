/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:48:02 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:30:26 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_check_format(char format, va_list *ap)
{
	if (format == '%')
		return (ft_put_chr_len('%'));
	else if (format == 'c')
		return (ft_put_chr_len(va_arg(*ap, int)));
	else if (format == 's')
		return (ft_put_str_len(va_arg(*ap, char *)));
	else if (format == 'p')
		return (ft_put_ptr_len(va_arg(*ap, unsigned long)));
	else if (format == 'd' || format == 'i')
		return (ft_put_nbr_len(va_arg(*ap, int)));
	else if (format == 'u')
		return (ft_put_base_len(va_arg(*ap, unsigned int), 10, 0));
	else if (format == 'x')
		return (ft_put_base_len(va_arg(*ap, unsigned int), 16, 0));
	else if (format == 'X')
		return (ft_put_base_len(va_arg(*ap, unsigned int), 16, 1));
	else
		return (0);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	char	*format;
	int		len;

	format = (char *)f;
	len = 0;
	va_start(ap, f);
	while (*format != '\0')
	{
		if (len == -1)
			return (-1);
		if (*format == '%')
		{
			format++;
			if (*format != '\0')
				len += ft_check_format(*format, &ap);
		}
		else
			len += ft_put_chr_len(*format);
		format++;
	}
	va_end(ap);
	return (len);
}
