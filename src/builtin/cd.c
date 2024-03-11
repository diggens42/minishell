/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/11 19:41:20 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO If ft_getenv does not find "HOME" in the environment, it will return NULL.
// Ensure your code handles this case before using home_path in string functions.

static char	*cd_tilde(char *content, char *home_path)
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

static void	cd_update_env(t_env **env, char *old_path, char *new_path)
{
	if (old_path)
		update_env(env, "OLDPWD", old_path);
	if (new_path)
		update_env(env, "PWD", new_path);
}

void	builtin_cd(t_token *token, t_env **env)
{
	char	*path;
	char	*home_path;
	char	*expanded_path;
	char	*old_path;
	char	*new_path;
	char	*old_pwd;

	expanded_path = NULL;
	old_path = getcwd(NULL, 0);
	home_path = ft_getenv("HOME", *env);
	if (token == NULL || (token->content[0] == '~' && ft_strcmp(token->content, "~") == 0))
		path = home_path;
	else if (ft_strcmp(token->content, "-") == 0)
	{
		old_pwd = ft_getenv("OLDPWD", *env);
		if (old_pwd)
		{
			path = old_pwd;
			printf("%s\n", path);
		}
		else
		{
			ft_printf("cd: OLDPWD not set"); //TODO error
			free(old_path);
			return ;
		}
	}
	else
	{
		expanded_path = cd_tilde(token->content, home_path);
		if (expanded_path != NULL)
			path = expanded_path;
		else
			path = token->content;
	}
	if (chdir(path) == -1)
		perror("chdir");
	else
	{
		new_path = getcwd(NULL, 0);
		cd_update_env(env, old_path, new_path);
		free(new_path);
	}
	if (expanded_path)
		free(expanded_path);
	free(old_path);
}
