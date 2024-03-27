/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:58:21 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 16:39:05 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_cmd(t_type	type)
{
	if (type == COMMAND)
		return (true);
	if (type == SINGLE_QUOTE)
		return (true);
	if (type == DOUBLE_QUOTE)
		return (true);
	if (type == DOLLAR)
		return (true);
	if (type == DQMARK)
		return (true);
	if (type == WILDCARD)
		return (true);
	return (false);
}

bool	is_operator(t_type type)
{
	if (type == PIPE)
		return (true);
	if (type == AND)
		return (true);
	if (type == OR)
		return (true);
	return (false);
}

t_ast	*ast_cmd(t_token **token)
{
	t_ast	*cmd_node;
	int		i;
	int		j;

	if (token == NULL || (*token) == NULL)
		return (NULL);
	cmd_node = new_ast_node(*token);
	i = 0;
	j = 0;
	while (*token != NULL && !is_operator((*token)->type))
	{
		if (is_redirect((*token)->type))
		{
			cmd_node->cmd->redir[i]->type = (*token)->type;
			advance_and_free_token(token);
			cmd_node->cmd->redir[i]->file = (*token)->content;
			advance_and_free_token(token);
			i++;
		}
		if (is_cmd((*token)->type))
		{
			cmd_node->cmd->argv[j] = (*token)->content;
			advance_and_free_token(token);
			j++;
		}
	}
	return (cmd_node);
}


// t_ast	*ast_cmd(t_token **token)
// {
// 	t_ast	*cmd_node;

// 	if (token == NULL || *token == NULL || (*token)->type != COMMAND)
// 		return NULL;
// 	cmd_node = new_ast_node(*token);
// 	advance_and_free_token(token);
// 	while (*token != NULL && (*token)->type == COMMAND)
// 		advance_and_free_token(token);
// 	if (*token && is_redirect((*token)->type))
// 		return (ast_redirect(token, cmd_node));
// 	return (cmd_node);
// }
