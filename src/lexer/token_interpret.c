/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_resolve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:40:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/11 19:23:39 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	interpret_token_content(t_token **token_head, t_env *env)
{
	t_token	*current;
	char	*expanded_content;
	
	if (token_head == NULL || *token_head == NULL)
		return ;
	current = *token_head;
	while (current != NULL)
	{
		if (current->type == DOLLAR)
		{
			expanded_content = expand_token_content(current->content, env);
			free(current->content);
			current->content = expanded_content;
			current->length = ft_strlen(expanded_content);
			current->type = WORD;
		}
		current = current->next;
	}
}
