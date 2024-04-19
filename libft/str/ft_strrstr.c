/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/13 16:43:01 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	const char	*last_occur;
	const char	*h;
	const char	*n;

	last_occur = NULL;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		h = haystack;
		n = needle;
		while (*h == *n && *n != '\0')
		{
			h++;
			n++;
		}
		if (*n == '\0')
			last_occur = haystack;
		haystack++;
	}
	return ((char *)last_occur);
}
