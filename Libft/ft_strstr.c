/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:02:25 by mott              #+#    #+#             */
/*   Updated: 2024/03/11 16:02:46 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	needlelen;

	needlelen = ft_strlen(needle);
	if (needlelen == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		if (ft_strncmp(&haystack[i], needle, needlelen) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
