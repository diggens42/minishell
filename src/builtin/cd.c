/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 17:25:25 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_chdir(char *dir, t_env **env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		perror("chdir");
		free(oldpwd);
		return (EXIT_FAILURE);
	}
	update_env(env, "OLDPWD", oldpwd);
	free(oldpwd);
	update_env(env, "PWD", dir);
	return (EXIT_SUCCESS);
}

bool	builtin_cd(char **argv, t_env **env)
{
	char	*dir;

	if (argv[1] == NULL || argv[1][0] == '~')
	{
		dir = ft_getenv("HOME", *env);
		if (dir == NULL)
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		if (dir != NULL && argv[1] != NULL && argv[1][1] != '\0')
			dir = ft_strjoin(dir, &argv[1][1]); // TODO need to free?
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		dir = ft_getenv("OLDPWD", *env);
		if (dir == NULL)
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		dir = argv[1];
	if (dir != NULL)
		ft_chdir(dir, env);
	return (true);
}
