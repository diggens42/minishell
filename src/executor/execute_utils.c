/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 21:29:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_pathname(t_token *tokens, t_env *env)
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

char	*find_pathname(char **path)
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

char	**tokens_to_char_array(t_token *tokens)
{
	char	**argv;
	int		n_tokens;
	int		i;

	n_tokens = tokens_size(tokens);
	// ft_printf("n_tokens: %d\n", n_tokens);
	argv = malloc(sizeof(char *) * (n_tokens + 1));
	if (argv == NULL)
		ft_exit();
	i = 0;
	while (i < n_tokens)
	{
		argv[i] = tokens->content;
		tokens = tokens->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**env_to_char_array(t_env *env)
{
	char	**envp;
	char	*temp;
	int		n_envp;
	int		i;

	n_envp = envp_size(env);
	envp = malloc(sizeof(char *) * (n_envp + 1));
	if (envp == NULL)
		ft_exit();
	i = 0;
	while (i < n_envp)
	{
		envp[i] = ft_strdup(env->key);
		temp = envp[i];
		envp[i] = ft_strjoin(temp, "=");
		free(temp);
		temp = envp[i];
		envp[i] = ft_strjoin(temp, env->value);
		free(temp);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	envp_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}
