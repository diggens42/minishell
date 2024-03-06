/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:22:53 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 13:36:43 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_env_to_char_array(t_env *env)
{
	char	**envp;
	char	*temp;
	int		n_envp;
	int		i;

	n_envp = ms_envp_size(env);
	envp = malloc(sizeof(char *) * (n_envp + 1));
	if (envp == NULL)
		ms_exit();
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

int	ms_envp_size(t_env *env)
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
