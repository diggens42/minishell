/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/08 20:16:09 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO export export
static t_env *builtin_export_sort(t_env *env) //TODO envp size in while loop
{
	t_env	*current;
	t_env	*previous;
	t_env	*temp;
	int		sorted;

	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		current = env;
		previous = NULL;
		while (current != NULL)
		{
			if (current->next != NULL && ft_strcmp(current->key, current->next->key) > 0)
			{
				temp = current->next;
				current->next = temp->next;
				temp->next = current;
				if (previous == NULL)
					env = temp;
				else
					previous->next = temp;
				sorted = 0;
			}
			previous = current;
			current = current->next;
		}
	}
	return (env);
}

static int	builtin_export_print(t_env *env)
{
	t_env	*temp;

	if (env == NULL)
		return (EXIT_SUCCESS);
	// temp = env;
	temp = builtin_export_sort(env);
	while (temp != NULL)
	{
		ft_printf("declare -x %s", temp->key);
		if (temp->value != NULL)
			ft_printf("=\"%s\"", temp->value);
		ft_printf("\n", temp->value);
		temp = temp->next;
	}
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
