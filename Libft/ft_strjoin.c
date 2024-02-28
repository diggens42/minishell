/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:44:55 by mott              #+#    #+#             */
/*   Updated: 2024/01/22 17:18:05 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*newstr;
	size_t	n;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	n = ft_strlen(str1) + ft_strlen(str2) + 1;
	newstr = (char *)malloc(n);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, str1, n);
	ft_strlcat(newstr, str2, n);
	return (newstr);
}
