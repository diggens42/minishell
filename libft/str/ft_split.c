/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:39:13 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	amount_substr(char *s, char c)
{
	size_t	amount;

	amount = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		amount++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (amount);
}

size_t	len_substr(char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != '\0' && *s != c)
		{
			len++;
			s++;
		}
		break ;
	}
	return (len);
}

char	*allocate_and_fill_substring(char const **s_ptr, size_t len)
{
	char	*substr;
	size_t	j;

	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	j = 0;
	while (j < len)
	{
		substr[j] = **s_ptr;
		(*s_ptr)++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

char	**fill_array(char **s_array, char const *s, char c, size_t amount)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s != '\0' && i < amount)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		len = len_substr((char *)s, c);
		s_array[i] = allocate_and_fill_substring(&s, len);
		if (!s_array[i])
		{
			while (i > 0)
				free(s_array[--i]);
			free(s_array);
			return (NULL);
		}
		i++;
	}
	s_array[i] = NULL;
	return (s_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	amount;
	char	**s_array;

	amount = amount_substr((char *)s, c);
	s_array = (char **)malloc((amount + 1) * sizeof(char *));
	if (!s_array)
		return (NULL);
	s_array = fill_array(s_array, s, c, amount);
	return (s_array);
}
