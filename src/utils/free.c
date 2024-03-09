/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:29:19 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 21:30:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	free_token_list(t_token *tokens)
// {
// 	t_token	*temp;

// 	while (tokens != NULL)
// 	{
// 		temp = tokens->next;
// 		free(tokens->content);
// 		free(tokens);
// 		tokens = temp;
// 	}
// }

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}
