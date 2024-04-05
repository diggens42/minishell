/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/05 18:40:08 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static const char *type_to_str(t_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == AND)
		return ("&&");
	else if (type == OR)
		return ("||");
	else
		return ("");
}

bool	operator_syntax(t_ast *node)
{
	const char	*token_str;
	bool 		left_error;
	bool		right_error;

	if (node == NULL)
		return (false);
	if (node->syntax_error == true)
	{
		token_str = type_to_str(node->type);
		if (token_str[0] != '\0')
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			ft_putstr_fd((char *)token_str, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
		}
		else if (node->cmd->redir[0] != NULL)
			ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
		return (true);
	}
	else
	{
		left_error = operator_syntax(node->left);
		right_error = operator_syntax(node->right);
	}
	return (left_error || right_error);
}
