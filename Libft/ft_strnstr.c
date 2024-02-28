/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:47:46 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 15:15:16 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	needlelen;

	needlelen = ft_strlen(needle);
	if (needlelen == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i + needlelen <= n)
	{
		if (ft_strncmp(&haystack[i], needle, needlelen) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
