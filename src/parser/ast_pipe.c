/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 16:36:52 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_pipe(t_token **token)
{
	t_ast	*node;
	t_ast	*pipe_node;
	t_ast	*r_node;

	node = ast_cmd(token);
	pipe_node = NULL;
	r_node = NULL;
	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe_node = new_ast_node(*token);
		*token = (*token)->next;
		r_node = ast_cmd(token);
		pipe_node->left = node;
		pipe_node->right = r_node;
		node = pipe_node;
	}
	return (node);
}
