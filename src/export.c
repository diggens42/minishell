/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 19:43:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_export(t_token *tokens, char **envp)
{
	char	*key;
	char	*val;
	char	*new_env_var;
	char	**envp_update;
	size_t	i;
	size_t	envp_size;
	size_t	new_env_var_size;
	
	if (tokens == NULL || envp == NULL)
		return ;
	envp_size = 0;
	while(envp[envp_size] != NULL)
		envp_size++;
	envp_update = (char **)malloc(sizeof(char *) * (envp_size + 1));
	if (envp_update == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < envp_size)
	{
		envp_update[i] = ft_strdup(envp[i]);
		if (envp_update[i] == NULL)
		{
			perror("malloc error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	while (tokens != NULL)
	{
		//TODO key & val into a struct
		key = ft_strtok(tokens->content, "=");
		val = ft_strtok(NULL, "=");
		if (key != NULL && val != NULL)
		{
			new_env_var_size = ft_strlen(key) + ft_strlen(val) + 2;
			new_env_var = (char *)malloc(new_env_var_size); //??
			if (new_env_var == NULL)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			ft_strlcpy(new_env_var, key, new_env_var_size);
			ft_strlcat(new_env_var, "=", new_env_var_size);
			ft_strlcpy(new_env_var, val, new_env_var_size);
			envp_update[envp_size] = new_env_var;
			envp_size++;
			envp_update[envp_size] = NULL;
			printf("Exported: %s\n", new_env_var);
		}
		tokens = tokens->next;
	}
	envp_size--;
	i = -1;
	while (++i < envp_size)
		free(envp[i]);
	free(envp);
	envp = envp_update;
}

// init envp in main as linekd list
// then we dont need to free odl envp
// make new_envp from the linekd list + new envp_vars