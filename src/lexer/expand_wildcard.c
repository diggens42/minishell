/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 00:06:36 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_parts(char *pattern)
{
	int		n_parts;

	n_parts = 1;
	while (*pattern != '\0')
	{
		if (*pattern == '*')
			n_parts++;
		pattern++;
	}
	return (n_parts);
}

static char	**alloc_and_split(char *pattern, int n_parts)
{
	char	**parts;
	char	*start;
	char	*pattern_ptr;
	int		idx;

	parts = (char **)ft_calloc(n_parts + 1, sizeof(char *));
	if (parts == NULL)
		return (NULL); //TODO handle malloc error
	start = pattern;
	pattern_ptr = pattern;
	idx = 0;
	while (*pattern_ptr != '\0')
	{
		if (*pattern_ptr == '*')
		{
			parts[idx++] = ft_strndup(start, pattern_ptr - start);
			start = pattern_ptr + 1;
		}
		pattern_ptr++;
	}
	parts[idx++] = ft_strndup(start, pattern_ptr - start);
	parts[idx] = NULL;
	return (parts);
}

char	**pattern_split(char *pattern)
{
	char	**parts;
	int		n_parts;

	n_parts = count_parts(pattern);
	parts = alloc_and_split(pattern, n_parts);
	return (parts);
}

int	wc_match(char *pattern, char *str)
{
	while (*pattern != '\0' && *str != '\0')
	{
		if (*pattern == '*')
			return (wc_match(pattern + 1, str) || wc_match(pattern, str + 1));
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}
