/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 18:22:50 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*prev;
	t_env	*new_env;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			if (value != NULL)
				current->value = ft_strdup(value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	new_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (new_env == NULL)
		ft_exit("malloc");
	new_env->key = ft_strdup(key);
	if (value != NULL)
		new_env->value = ft_strdup(value);
	if (prev == NULL)
		*env = new_env;
	else
		prev->next = new_env;
}

bool	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*key;
	char	*equal_sign;
	char	*value;

	if (argv[1] == NULL)
	{
		while (*env != NULL)
		{
			ft_printf("declare -x %s", (*env)->key);
			if ((*env)->value != NULL)
				ft_printf("=\"%s\"", (*env)->value);
			ft_printf("\n", (*env)->value);
			*env = (*env)->next;
		}
		return (true);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		key = ft_strdup(argv[i]);
		value = NULL;
		equal_sign = ft_strchr(key, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			value = equal_sign + 1;
		}
		update_env(env, key, value);
		free(key);
		i++;
	}
	return (true);
}
