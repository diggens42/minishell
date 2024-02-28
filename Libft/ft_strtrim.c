/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:42 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 19:24:36 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	end;
	char	*newstr;

	start = 0;
	while (str[start] != '\0' && ft_strchr(set, str[start]) != NULL)
		start++;
	end = ft_strlen(str);
	while (end > start && ft_strchr(set, str[end - 1]) != NULL)
		end--;
	newstr = ft_substr(str, start, end - start);
	return (newstr);
}
