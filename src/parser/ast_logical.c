/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:27 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/26 18:32:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_logical(t_type type)
{
	return(type == AND || type == OR);
}


// t_ast	*ast_logical(t_token **token, t_ast *left)
// {
// 	t_ast	*node;
// 	t_ast	*logical;
// 	t_token	*next_token;

// 	node = left;
// 	logical = NULL;
// 	while (*token != NULL && is_logical((*token)->type))
// 	{
// 		logical = new_ast_node(*token);
// 		logical->left = node;
// 		next_token = (*token)->next;
// 		free_token(*token);
// 		*token = next_token;
// 		node->right = ast_cmd(token);
// 		// else handle syntax error
// 		node = logical;
// 		if (*token == NULL || !is_logical((*token)->type))
// 			break ;
// 	}
// 	return (node);
// }

t_ast	*ast_logical(t_token **token, t_ast *left)
{
	t_ast	*node;
	t_ast	*logical;
	t_token	*next_token;
	t_ast	*right;

	node = left;
	logical = NULL;
	while (*token != NULL && is_logical((*token)->type))
	{
		logical = new_ast_node(*token);
		logical->left = node;
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
		if (*token != NULL && (*token)->type == PARENTHESIS_L)
		{
			right = ast_parenthesis(token);
			logical->right = right;
		}
		if (*token != NULL && (*token)->type == COMMAND)
		{
			right = new_ast_node(*token);
			while (*token != NULL && (*token)-> type == COMMAND)
			{
				next_token = (*token)->next;
				free_token(*token);
				*token = next_token;
			}
			logical->right = right;
		}
		// else handle syntax error
		node = logical;
		if (*token == NULL || !is_logical((*token)->type))
			break ;
	}
	return (node);
}
