/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:57:08 by mott              #+#    #+#             */
/*   Updated: 2023/10/27 18:04:53 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_substr_count(const char *str, char c)
{
	size_t	num_of_strs;
	size_t	i;

	num_of_strs = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			num_of_strs++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (num_of_strs);
}

static size_t	ft_substr_len(const char *substr, char c)
{
	size_t	i;

	i = 0;
	while (substr[i] != '\0' && substr[i] != c)
		i++;
	return (i);
}

static void	ft_free(char **array_of_strs)
{
	size_t	i;

	i = 0;
	while (array_of_strs[i] != NULL)
	{
		free(array_of_strs[i]);
		array_of_strs[i] = NULL;
		i++;
	}
	free(array_of_strs);
	array_of_strs = NULL;
}

char	**ft_split(const char *str, char c)
{
	char	**array_of_strs;
	size_t	i;
	size_t	j;
	size_t	n_substr;

	n_substr = ft_substr_count(str, c);
	array_of_strs = (char **)malloc((n_substr + 1) * sizeof(char *));
	if (array_of_strs == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n_substr)
	{
		while (str[j] != '\0' && str[j] == c)
			j++;
		array_of_strs[i] = ft_substr(str, j, ft_substr_len(&str[j], c));
		if (array_of_strs[i++] == NULL)
		{
			ft_free(array_of_strs);
			return (NULL);
		}
		j += ft_substr_len(&str[j], c);
	}
	array_of_strs[i] = NULL;
	return (array_of_strs);
}
