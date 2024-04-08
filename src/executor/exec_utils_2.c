/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/04/06 16:29:27 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_char_array(t_env *env)
{
	char	**envp;
	char	*temp;
	int		n;
	int		i;

	n = envp_size(env);
	envp = (char **)ft_calloc(n + 1, sizeof(char *));
	if (envp == NULL)
		ft_perror("malloc", strerror(errno));
	i = 0;
	while (i < n)
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

char	*ft_tolower_str(char *str)
{
	char	*lower;
	int		i;

	lower = ft_strdup(str);
	if (lower == NULL)
	{
		ft_perror("malloc", strerror(errno));
		return (NULL);
	}
	i = 0;
	while (lower[i] != '\0')
	{
		lower[i] = ft_tolower(str[i]);
		i++;
	}
	return (lower);
}
