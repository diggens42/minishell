/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:37:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// locate last occurrence of char 'c' in string 's'
// if searchingfor null terminator, return end of string
// otherwise iterate through string 
//   update last_occur everytime 's' and 'c' are matching

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occur;

	last_occur = NULL;
	if ((unsigned char)c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			last_occur = s;
		s++;
	}
	return ((char *)last_occur);
}
