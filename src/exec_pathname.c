/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pathname.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:41:05 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 17:41:33 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_create_pathname(t_token *tokens, t_env *env)
{
	char	**path;
	char	*temp;
	int		i;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			temp = env->value;
		env = env->next;
	}
	path = ft_split(temp, ':');
	i = 0;
	while (path[i] != NULL)
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		free(temp);
		temp = path[i];
		path[i] = ft_strjoin(temp, tokens->content);
		free(temp);
		i++;
	}
	return (path);
}

char	*ms_find_pathname(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}
