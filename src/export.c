/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:06:05 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/03 19:43:35 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_env_vars(t_env **env, char key, char *value)
{
	t_env	*current;
	t_env	*last;
	t_env	*new_env_var;

	current = env;
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
		return (NULL);
	//TODO ADD MALLOC ERROR
	new_env_var->key = ft_strdup(key);
	new_env_var->value = ft_strdup(value);
	new_env_var->next = NULL;
	last->next = new_env_var;
}

void	ms_export(char t_token *token, t_env *env)
{
	char	*token_content;
	char	*equals_ptr;
	char	*key;
	char	*value;

	if (token != NULL && token->content != NULL)
	{
		token_content = token->content;
		equals_ptr = ft_strchr(token_content, "=");
		if (equals_ptr != NULL)
		{
			*equals_ptr = '\0';
			key = token_content;
			value = equals_ptr + 1;
			update_env_vars(env, key, value);
			*equals_ptr = '=';
		}
	}
}
