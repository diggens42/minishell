/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:50:26 by mott              #+#    #+#             */
/*   Updated: 2024/04/18 19:50:46 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
