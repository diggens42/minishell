/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:29:19 by mott              #+#    #+#             */
/*   Updated: 2024/04/07 19:27:19 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token_list(t_token *token_head)
{
	t_token	*temp;

	while (token_head != NULL)
	{
		temp = token_head->next;
		free(token_head->content);
		free(token_head);
		token_head = temp;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	free_char_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_type_array(t_type **type)
{
	int	i;

	i = 0;
	while (type[i] != NULL)
	{
		free(type[i]);
		i++;
	}
	free(type);
}
