/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:33:09 by mott              #+#    #+#             */
/*   Updated: 2024/01/26 13:02:26 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	a;
	size_t			i;

	str = (unsigned char *)b;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
		str[i++] = a;
	return (b);
}
