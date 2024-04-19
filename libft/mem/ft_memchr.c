/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:55:02 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. scans a memory block (*s) to find a specified character c
// 2. returns a pointer to the first occurence of that character
//    within the specified length 'n' 
// 3. returns NULL if char is not found

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		val;
	size_t				i;

	str = (unsigned char *)s;
	val = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == val)
		{
			return ((void *)(str + i));
		}
		i++;
	}
	return (NULL);
}
