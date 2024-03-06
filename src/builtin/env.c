/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:52:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 20:07:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (node == NULL)
		return (NULL);
	//TODO ADD MALLOC ERROR
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

t_env	*init_env(char **envp)
{
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
	return (env);
}
