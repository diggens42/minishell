/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:19:33 by mott              #+#    #+#             */
/*   Updated: 2024/03/23 16:24:44 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (EXIT_FAILURE);
	while (key[++i] != '\0')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	env_new(t_env **env, t_env *previous, char *key, char *value)
{
	t_env	*new_env;

	if (is_valid_key(key) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	new_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (new_env == NULL)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	new_env->key = ft_strdup(key);
	if (value != NULL)
		new_env->value = ft_strdup(value);
	if (previous == NULL)
		*env = new_env;
	else
		previous->next = new_env;
	return (EXIT_SUCCESS);
}

int	env_update(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current != NULL)
	{
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
