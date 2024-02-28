/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:04:58 by mott              #+#    #+#             */
/*   Updated: 2024/02/12 15:56:45 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*gnl_strjoin(const char *str1, const char *str2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	newstr = (char *)malloc(gnl_strlen(str1) + gnl_strlen(str2) + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	if (str1 != NULL)
	{
		while (str1[i] != '\0')
		{
			newstr[i] = str1[i];
			i++;
		}
	}
	j = 0;
	while (str2[j] != '\0')
	{
		newstr[i + j] = str2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*gnl_substr(const char *str, size_t start, size_t n)
{
	char	*substr;
	size_t	i;

	if (str == NULL)
		return (NULL);
	substr = (char *)malloc(n + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (str[start] != '\0' && i < n)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
