/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 18:26:17 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*builtin_export_copy(t_env *env)
{
	t_env	*temp;

	temp = NULL;
	while (env != NULL)
	{
		append_env_node(&temp, new_env_node(env->key, env->value));
		env = env->next;
	}
	return (temp);
}

static int	builtin_export_size(t_env *env)
{
	int		env_size;
	t_env	*current;

	env_size = 0;
	current = env;
	while (current != NULL)
	{
		env_size++;
		current = current->next;
	}
	return (env_size);
}

static void builtin_export_swap(t_env **env, t_env **previous, t_env **current)
{
	t_env	*next;

	next = (*current)->next;
	(*current)->next = next->next;
	next->next = *current;
	if (*previous == NULL)
		*env = next;
	else
		(*previous)->next = next;
	*previous = next;
}

static void	builtin_export_sort(t_env **env, int env_size)
{
	t_env	*previous;
	t_env	*current;

	while (env_size-- >= 0)
	{
		previous = NULL;
		current = *env;
		while (current != NULL && current->next != NULL)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
				builtin_export_swap(env, &previous, &current);
			else
			{
				previous = current;
				current = current->next;
			}
		}
	}
}

static int	builtin_export_print(t_env *env)
{
	t_env	*temp;
	t_env	*temp2;
	int		env_size;

	if (env == NULL)
		return (EXIT_SUCCESS);
	temp = builtin_export_copy(env);
	env_size = builtin_export_size(temp);
	builtin_export_sort(&temp, env_size);
	temp2 = temp;
	while (temp != NULL)
	{
		ft_printf("declare -x %s", temp->key);
		if (temp->value != NULL)
			ft_printf("=\"%s\"", temp->value);
		ft_printf("\n", temp->value);
		temp = temp->next;
	}
	free_env_list(temp2);
	return (EXIT_SUCCESS);
}

int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*key;
	char	*equal_sign;
	char	*value;
	int		exit_status;

	if (argv[1] == NULL)
		return (builtin_export_print(*env));
	exit_status = EXIT_SUCCESS;
	i = 0;
	while (argv[++i] != NULL)
	{
		key = ft_strdup(argv[i]);
		value = NULL;
		equal_sign = ft_strchr(key, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			value = equal_sign + 1;
		}
		if (env_update(env, key, value) == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		free(key);
	}
	return (exit_status);
}
