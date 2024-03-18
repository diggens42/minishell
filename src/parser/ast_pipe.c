/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/18 16:00:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//OK
t_ast	*ast_pipe(t_token **token, t_ast *left)
{
	t_ast	*pipe;
	t_ast	*right;
	t_token	*next_token;
	
	pipe = NULL;
	right = NULL;
	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe = new_ast_node(*token);
		next_token = (*token)->next;
		free_token(*token);
		*token = next_token;
		pipe->left = left;
		right = ast_cmd(token);
		pipe->right = right;
		left = pipe;
	}
	return (left);
}
