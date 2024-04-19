/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/19 17:46:08 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*builtin_cd_home(char **argv, t_env **env)
{
	char	*dir;

	dir = ft_getenv("HOME", *env);
	if (dir == NULL)
		ft_perror("cd", "HOME not set");
	if (dir != NULL && argv[1] != NULL && argv[1][1] != '\0')
	{
		dir = ft_strjoin(dir, &argv[1][1]);
		if (dir == NULL)
			ft_perror("malloc", "malloc fail");
	}
	return (dir);
}

static char	*builtin_cd_oldpwd(t_env **env)
{
	char	*dir;

	dir = ft_getenv("OLDPWD", *env);
	if (dir == NULL)
		ft_perror("cd", "OLDPWD not set");
	else
	{
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (dir);
}

static int	ft_chdir(char *dir, t_env **env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		ft_perror("chdir", strerror(errno));
		free(dir);
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	env_update(env, "OLDPWD", oldpwd);
	free(oldpwd);
	env_update(env, "PWD", dir);
	free(dir);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **argv, t_env **env)
{
	char	*dir;

	if (argv[1] == NULL || argv[1][0] == '~' || argv[1][0] == '\0')
	{
		dir = builtin_cd_home(argv, env);
		if (dir == NULL)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		dir = builtin_cd_oldpwd(env);
		if (dir == NULL)
			return (EXIT_FAILURE);
	}
	else
		dir = argv[1];
	return (ft_chdir(ft_strdup(dir), env));
}
