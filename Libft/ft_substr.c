/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:42:42 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 16:34:27 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t n)
{
	char	*substr;
	size_t	strlen;

	strlen = ft_strlen(str);
	if (start > strlen)
		return (ft_strdup(""));
	if (start + n > strlen)
		n = strlen - start;
	substr = (char *)malloc(n + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &str[start], n + 1);
	return (substr);
}
