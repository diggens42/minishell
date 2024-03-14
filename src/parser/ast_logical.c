/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:27 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/14 18:13:39 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_logical(t_token_type type)
{
	return(type == AND || type == OR);
}

t_ast	*ast_logical(t_token **token, t_ast *left)
{
	t_ast	*node;
	t_ast	*logical;

	node = left;
	logical = NULL;
	while (*token != NULL)
	{
		if (is_logical((*token)->type))
		{
			logical = new_ast_node(*token);
			logical->left = node;
			*token = (*token)->next;
			logical->right = ast_pipe(token, NULL);
			node = logical;
		}
		else
			break ;
	}
	return (node);
}
