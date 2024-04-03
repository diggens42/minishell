/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:17:31 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/03 18:46:21 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//OK
t_ast	*ast_pipe(t_token **token, t_ast *left)
{
	t_ast	*pipe;

	while (*token != NULL && (*token)->type == PIPE)
	{
		if (left == NULL)
			ft_printf("syntax error near unexpected token '%s'\n", (*token)->content); //TODO ft_exit
		pipe = new_ast_node(*token);
		pipe->left = left;
		advance_and_free_token(token);
		if (is_logical((*token)->type))
			ft_printf("syntax error near unexpected token '%s'\n", (*token)->content); //TODO ft_exit
		pipe->right = ast_cmd(token);
		left = pipe;
	}
	return (left);
}
