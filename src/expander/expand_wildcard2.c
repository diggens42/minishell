/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/04 16:29:24 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a given string matches a wildcard pattern
int	match_wildcard(char *pattern, char *str)
{
	while (*pattern != '\0' && *str != '\0')
	{
		if (*pattern == '*')
			return (match_wildcard(pattern + 1, str) || match_wildcard(pattern, str + 1));
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

//converts paths of wildcard matches into tokens
void	wildcard_path_to_token(char *path, t_token **current)
{
	t_token	*new_token;

	while (path != NULL)
	{
		new_token = token_new();
		new_token->content = ft_strdup(path);
		new_token->length = ft_strlen(path);
		new_token->type = COMMAND;
		token_add_back(current, new_token);
		path = ft_strtok(NULL, " ");
	}
}
