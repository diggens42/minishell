/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:27 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/22 18:36:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_logical(t_type type)
{
	return(type == AND || type == OR);
}

t_ast	*ast_logical(t_token **token, t_ast *left)
{
	t_ast	*node;
	t_ast	*logical;
	t_token	*next_token;

	node = left;
	logical = NULL;
	while (*token != NULL && is_logical((*token)->type))
	{
		logical = new_ast_node(*token);
		logical->left = node;
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
		logical->right = ast_parser(token);
		node = logical;
		if (*token == NULL || !is_logical((*token)->type))
			break ;
	}
	return (node);
}
