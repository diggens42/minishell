/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:21:52 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 13:30:47 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// extracs variable names starting after a '$' sign
// and ending before first slash ('/') or null terminator ('\0')
static char	*extract_var_name(const char *content)
{
	char	*slash_pos;
	char	*var_name;
	size_t	var_name_len;

	slash_pos = ft_strchr(content, '/');
	if (slash_pos != NULL)
		var_name_len = slash_pos - content - 1;
	else
		var_name_len = ft_strlen(content) - 1;
	var_name = (char *)ft_calloc(var_name_len + 1, sizeof(char));
	if (!var_name)
		ft_perror("malloc", strerror(errno));
	if (var_name)
		ft_strlcpy(var_name, content + 1, var_name_len + 1);
	return (var_name);
}

// constructs new string by replacing '$' prefixed variable with its env value
static char	*construct_new_content(const char *var_value, const char *content)
{
	char	*slash_pos;
	char	*new_content;
	size_t	var_value_len;
	size_t	after_slash_len;
	size_t	new_content_len;

	slash_pos = ft_strchr(content, '/');
	var_value_len = ft_strlen(var_value);
	after_slash_len = 0;
	if (slash_pos != NULL)
		after_slash_len = ft_strlen(slash_pos);
	new_content_len = var_value_len + after_slash_len;
	new_content = (char *)ft_calloc(new_content_len + 1, sizeof(char));
	if (!new_content)
		ft_perror("malloc", strerror(errno));
	if (new_content)
	{
		ft_memcpy(new_content, var_value, var_value_len);
		if (slash_pos)
			ft_memcpy(new_content + var_value_len, slash_pos, after_slash_len);
		new_content[new_content_len] = '\0';
	}
	return (new_content);
}

// replaces variables prefixed with $ (e.g. $HOME)
// with their corresponding environment values
char	*expand_dollar_sign(t_mini *mini, const char *content)
{
	char	*var_name;
	char	*var_value;
	char	*expanded_content;

	var_name = extract_var_name(content);
	var_value = ft_strdup(ft_getenv(var_name, mini->env));
	if (!var_value)
		var_value = ft_strdup("");
	expanded_content = construct_new_content(var_value, content);
	free(var_name);
	free(var_value);
	return (expanded_content);
}
