/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:26:57 by mott              #+#    #+#             */
/*   Updated: 2024/03/24 18:17:39 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_absolute_path(char *command)
{
	char	*pathname;

	pathname = ft_strdup(command);
	if (access(pathname, X_OK) == -1)
	{
		ft_perror(command, strerror(errno));
		if (errno == 13)
			exit(126);
		else
			exit(127);
	}
	return (pathname);
}

char	*create_relative_path(char *command, t_env *env)
{
	char	**path;
	char	*pathname;

	path = split_path(command, env);
	pathname = find_pathname(path);
	free_char_array(path);
	if (pathname == NULL)
	{
		ft_perror(command, "command not found");
		exit(127);
	}
	return (pathname);
}

char	**split_path(char *command, t_env *env)
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
		path[i] = ft_strjoin(temp, command);
		free(temp);
		i++;
	}
	return (path);
}

char	*find_pathname(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (access(path[i], X_OK) == 0)
			return (ft_strdup(path[i]));
		i++;
	}
	return (NULL);
}
