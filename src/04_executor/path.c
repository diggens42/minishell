/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:26:57 by mott              #+#    #+#             */
/*   Updated: 2024/04/19 22:07:35 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**split_path(char *command, t_env *env)
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

static char	*find_pathname(char **path)
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

char	*create_absolute_path(t_mini *mini, char *pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode) == true)
		{
			ft_perror(pathname, "is a directory");
			ft_exit(mini, PERMISSION_ERROR);
		}
	}
	if (access(pathname, X_OK) == ERROR)
	{
		ft_perror(pathname, strerror(errno));
		if (errno == 13)
			ft_exit(mini, PERMISSION_ERROR);
		else
			ft_exit(mini, PATH_ERROR);
	}
	return (ft_strdup(pathname));
}

char	*create_relative_path(t_mini *mini, char *command)
{
	char	**path;
	char	*pathname;

	path = split_path(command, mini->env);
	pathname = find_pathname(path);
	ft_free_strarray(path);
	if (pathname == NULL)
	{
		ft_perror(command, "command not found");
		ft_exit(mini, PATH_ERROR);
	}
	return (pathname);
}
