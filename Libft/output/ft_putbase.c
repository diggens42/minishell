/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 00:11:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putbase(unsigned long num, int base, int upper)
{
	static const char	set[] = "0123456789abcdef";
	char				c;

	if (num >= (unsigned long)base)
		ft_putbase(num / base, base, upper);
	c = set[num % base];
	if (upper == 1)
		c = ft_toupper(c);
	write(STDOUT_FILENO, &c, 1);
}
