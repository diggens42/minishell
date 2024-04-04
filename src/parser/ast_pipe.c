/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/04 20:20:58 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ast_pipe(t_token **token, t_ast *left)
{
	t_ast	*pipe;

	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe = new_ast_node(*token);
		pipe->left = left;
		advance_and_free_token(token);
		if (is_logical((*token)->type))
			pipe->syntax_error = true;
		pipe->right = ast_cmd(token);
		if (pipe->left == NULL || pipe->right == NULL)
			pipe->syntax_error = true;
		left = pipe;
	}
	return (left);
}
