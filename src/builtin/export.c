/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/23 14:23:14 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	builtin_export_print(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		ft_printf("declare -x %s", current->key);
		if (current->value != NULL)
			ft_printf("=\"%s\"", current->value);
		ft_printf("\n", current->value);
		current = current->next;
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
		return (builtin_export_print(env));
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
		if (builtin_env_update(env, key, value) == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		free(key);
	}
	return (exit_status);
}
