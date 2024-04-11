/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:34:32 by mott              #+#    #+#             */
/*   Updated: 2024/04/11 23:10:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (node == NULL)
		return (NULL);//TODO ADD MALLOC ERROR
	if (key != NULL)
	{
		node->key = ft_strdup(key);
		if (node->key == NULL)
		{
			free(node);
			return (NULL);
		}
	}
	if (value != NULL)
	{
		node->value = ft_strdup(value);
		if (node->value == NULL)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	return (node);
}

t_env	*init_env(char **envp)
{
	// extern **environ;
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		key = ft_strtok(envp[i], "=");
		value = ft_strtok(NULL, "=");
		if (key && value)
			append_env_node(&env, new_env_node(key, value));
		i++;
	}
	env->exit_status = 0;
	return (env);
}

char	*ft_getenv(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
