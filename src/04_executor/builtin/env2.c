/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:19:33 by mott              #+#    #+#             */
/*   Updated: 2024/04/19 20:45:01 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid_key(char *key, char *builtin)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
	{
		ft_perror_2(builtin, key, "not a valid identifier");
		return (EXIT_FAILURE);
	}
	while (key[++i] != '\0')
	{
		if (key[i] == '+' && key[i + 1] == '\0')
			return (EXIT_SUCCESS);
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
		{
			ft_perror_2(builtin, key, "not a valid identifier");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	env_new(t_env **env, t_env *previous, char *key, char *value)
{
	t_env	*new_env;

	if (is_valid_key(key, "export") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (new_env == NULL)
	{
		ft_perror("malloc", "malloc fail");
		return (EXIT_FAILURE);
	}
	if (key[ft_strlen(key) - 1] == '+')
		key[ft_strlen(key) - 1] = '\0';
	new_env->key = ft_strdup(key);
	if (value != NULL)
		new_env->value = ft_strdup(value);
	if (previous == NULL)
		*env = new_env;
	else
		previous->next = new_env;
	return (EXIT_SUCCESS);
}

static void	env_append(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = *env;
	if (ft_strncmp(current->key, key, ft_strlen(key) - 1) == 0)
	{
		if (value != NULL)
			current->value = ft_strjoin_free(current->value, value);
	}
}

int	env_update(t_env **env, char *key, char *value)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = *env;
	while (current != NULL)
	{
		if (key[ft_strlen(key) - 1] == '+')
		{
			env_append(env, key, value);
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			if (value != NULL)
				current->value = ft_strdup(value);
			return (EXIT_SUCCESS);
		}
		previous = current;
		current = current->next;
	}
	return (env_new(env, previous, key, value));
}
