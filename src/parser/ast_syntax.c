/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/04 20:42:21 by fwahl            ###   ########.fr       */
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

bool	syntax_check(t_ast *node)
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
			ft_printf("syntax error near unexpected token `%s'\n", token_str);
		else if (node->cmd->redir[0] != NULL)
			ft_printf("syntax error near unexpected token `newline'\n");
		else
			ft_printf("syntax error\n");
		return (true);
	}
	else
	{
		left_error = syntax_check(node->left);
		right_error = syntax_check(node->right);
	}
	return (left_error || right_error);
}
