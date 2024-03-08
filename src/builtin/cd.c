/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/08 22:26:30 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO If ft_getenv does not find "HOME" in the environment, it will return NULL.
// Ensure your code handles this case before using home_path in string functions.
//TODO cd - functionality

static char	*expand_path_tilde(char *content, char *home_path)
{
	char	*path;
	size_t	new_path_len;

	new_path_len = 0;
	if (content[0] == '~' && ft_strcmp(content, "~") != 0)
	{
		new_path_len = ft_strlen(home_path) + ft_strlen(content);
		path = malloc(sizeof(char) * (new_path_len));
		if (path == NULL)
		{
			perror("malloc");//TODO handle malloc error
			return (NULL);
		}
		ft_strlcpy(path, home_path, new_path_len);
		ft_strlcat(path, content + 1, new_path_len);
		return (path);
	}
	return (NULL);
}

void	builtin_cd(t_token *token, t_env *env)
{
	char	*path;
	char	*home_path;
	char	*expanded_path;

	home_path = ft_getenv("HOME", env);
	if (token == NULL || (token->content[0] == '~' && ft_strcmp(token->content, "~") == 0))
		path = home_path;
	else
	{
		expanded_path = expand_path_tilde(token->content, home_path);
		if (expanded_path != NULL)
			path = expanded_path;
		else
			path = token->content;
	}
	if (chdir(path) == -1)
		perror("chdir");
	if (token != NULL && token->content[0] == '~' && path != home_path)
		free(path);
}
