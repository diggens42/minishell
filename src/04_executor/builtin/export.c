/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/18 20:30:46 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static void	builtin_export_swap(t_env **env, t_env **previous, t_env **current)
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

int	builtin_export_print(t_env *env)
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(temp->key, STDOUT_FILENO);
		if (temp->value != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(temp->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = temp->next;
	}
	free_env_list(temp2);
	return (EXIT_SUCCESS);
}
