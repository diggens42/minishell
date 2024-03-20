/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 19:32:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
