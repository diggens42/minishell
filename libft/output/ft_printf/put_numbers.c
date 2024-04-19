/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:08:56 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 15:30:14 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

unsigned long	ft_put_base_len(unsigned long num, int base, int upper)
{
	static const char	set[] = "0123456789abcdef";
	char				c;
	int					len;

	len = 0;
	if (num >= (unsigned long)base)
		len += ft_put_base_len(num / base, base, upper);
	if (len == -1)
		return (-1);
	c = set[num % base];
	if (upper == 1)
		c = ft_toupper(c);
	len += write(STDOUT_FILENO, &c, 1);
	if (len == -1)
		return (-1);
	return (len);
}

int	ft_put_nbr_len(long num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		len += ft_put_chr_len('-');
		if (len == -1)
			return (-1);
		num = -num;
	}
	len += ft_put_base_len(num, 10, 0);
	return (len);
}

int	ft_put_ptr_len(unsigned long num)
{
	int	len;
	int	ret;

	ret = ft_put_str_len("0x");
	if (ret == -1)
		return (-1);
	len = ft_put_base_len(num, 16, 0) + 2;
	if (len == -1)
		return (-1);
	return (len);
}
