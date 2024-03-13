/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:27 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 16:38:15 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_logical(t_token **token)
{
	t_ast	*node;
	t_ast	*new_node;

	node = ast_pipe(token);
	new_node = NULL;
	while (*token != NULL)
	{
		if ((*token)->type == AND || (*token)->type == OR)
		{
			new_node = new_ast_node(*token);
			new_node->left = node;
			*token = (*token)->next;
			new_node->right = ast_pipe(token);
			node = new_node;
		}
		else
			break ;
	}
	return (node);
}
