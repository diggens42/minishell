/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 19:43:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	wildcard_prefix(const char *prefix, const char *str)
{
	size_t	prefix_len;
	size_t	str_len;

	if (prefix == NULL || str == NULL)
		return (false);
	prefix_len = ft_strlen(prefix);
	str_len = ft_strlen(str);
	if (str_len < prefix_len)
		return (false);
	return (ft_strncmp(prefix, str, prefix_len) == 0);
}

static bool	wildcard_suffix(const char *suffix, const char *str)
{
	size_t	suffix_len;
	size_t	str_len;

	if (suffix == NULL || str == NULL)
		return (false);
	suffix_len = ft_strlen(suffix);
	str_len = ft_strlen(str);
	if (suffix_len > str_len)
		return (false);
	return (ft_strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0);
}

bool	analyze_pattern(const char *pattern, const char *file)
{
	const char	*wildcard = ft_strchr(pattern, '*');
	const char	*suffix;
	char		*prefix;
	bool		result;

	if (wildcard == pattern)
		return (wildcard_suffix(pattern + 1, file));
	else if (*(wildcard + 1) == '\0')
	{
		prefix = ft_strndup(pattern, wildcard - pattern);
		result = wildcard_prefix(prefix, file);
		free(prefix);
		return (result);
	}
	else
	{
		prefix = ft_strndup(pattern, wildcard - pattern);
		suffix = wildcard + 1;
		result = wildcard_prefix(prefix, file) && wildcard_suffix(suffix, file);
		free(prefix);
		return (result);
	}
}

char	*expand_wildcard(char *content)
{
	char	*expanded_content;

	expanded_content = content;
	
	return (expanded_content);
}
