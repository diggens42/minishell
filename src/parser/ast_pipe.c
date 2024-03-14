/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/14 18:03:16 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//OK
t_ast	*ast_pipe(t_token **token, t_ast *left)
{
	t_ast	*pipe;
	t_ast	*right;
	
	pipe = NULL;
	right = NULL;
	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe = new_ast_node(*token);
		pipe->left = left;
		*token = (*token)->next;
		right = ast_cmd(token);
		pipe->right = right;
		left = pipe;
	}
	return (left);
}
