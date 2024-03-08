/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/07 16:46:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO If ft_getenv does not find "HOME" in the environment, it will return NULL.
// Ensure your code handles this case before using home_path in string functions.
//TODO cd - functionality
void	builtin_cd(t_token *token, t_env *env)
{
	char	*path;
	char	*home_path;
	size_t	new_path_len;

	new_path_len = 0;
	home_path = ft_getenv("HOME", env);
	if (token == NULL || ft_strcmp(token->content, "~") == 0)
		path = home_path;
	else if (token->content[0] == '~')
	{
		new_path_len = ft_strlen(home_path) + ft_strlen(token->content);
		path = malloc(sizeof(char) * (new_path_len));
		if (path == NULL)
		{
			perror("malloc");
			return ;
		}
		ft_strlcpy(path, home_path, new_path_len);
		ft_strlcat(path, token->content + 1, new_path_len);
	}
	else
		path = token->content;
	if (chdir(path) == -1)
		perror("chdir");
	if (token != NULL && token->content[0] == '~' && path != home_path)
		free(path);
}