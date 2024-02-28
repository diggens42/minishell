/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:38:40 by mott              #+#    #+#             */
/*   Updated: 2024/01/26 13:02:06 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d < s)
		ft_memcpy(dst, src, n);
	else if (d > s)
	{
		i = 0;
		while (i < n)
		{
			d[n] = s[n];
			i++;
		}
	}
	return (dst);
}
