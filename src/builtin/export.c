/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/08 21:29:08 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_env(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*last;
	t_env	*new_env_var;

	current = *env;
	last = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		last = current;
		current = current->next;
	}
	new_env_var = (t_env *)ft_calloc(1, sizeof(t_env));
	if (new_env_var == NULL)
		return ;
	//TODO ADD MALLOC ERROR
	new_env_var->key = ft_strdup(key);
	new_env_var->value = ft_strdup(value);
	new_env_var->next = NULL;
	last->next = new_env_var;
}

void	builtin_export(t_token *tokens, t_env *env)
{
	t_token	*token;
	char	*equals_ptr;
	bool	assignment;

	assignment = false;
	token = tokens->next;
	while (token != NULL)
	{
		if (token->content != NULL)
		{
			equals_ptr = ft_strchr(token->content, '=');
			if (equals_ptr != NULL)
			{
				*equals_ptr = '\0';
				update_env(&env, token->content, equals_ptr + 1);
				*equals_ptr = '=';
				assignment = true;
			}
		}
		token = token->next;
	}
	if (assignment == false)
		builtin_env(env);
}
