/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:21:46 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 20:23:08 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ast_redirect(t_ast *cmd_node, t_token **token, int *i)
{
	cmd_node->cmd->redir[*i]->type = (*token)->type;
	advance_and_free_token(token);
	cmd_node->cmd->redir[*i]->file = ft_strdup((*token)->content);
	advance_and_free_token(token);
	(*i)++;
}
