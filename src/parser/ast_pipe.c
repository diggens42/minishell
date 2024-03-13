/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 21:14:04 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_pipe(t_token **token, t_ast *last_node)
{
	t_ast	*pipe_node;
	t_ast	*r_node;
	t_ast	*prev_node;
	
	prev_node = last_node;
	pipe_node = NULL;
	r_node = NULL;
	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe_node = new_ast_node(*token);
		pipe_node->left = last_node;
		*token = (*token)->next;
		r_node = ast_cmd(token);
		pipe_node->right = r_node;
		last_node = pipe_node;
	}
	if (pipe_node != NULL)
		return (pipe_node);
	else
		return (last_node);
}
