/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/15 15:00:49 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**tokens_to_char_array(t_token *tokens)
{
	char	**argv;
	int		n_tokens;
	int		i;

	n_tokens = tokens_size(tokens);
	argv = (char **)ft_calloc(n_tokens + 1, sizeof(char *));
	if (argv == NULL)
		ft_exit("malloc");
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
	envp = (char **)ft_calloc(n_envp + 1, sizeof(char *));
	if (envp == NULL)
		ft_exit("malloc");
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
