/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/06 15:58:14 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	operator_syntax(t_token *token)
{
	t_token *check;
	t_token *prev;

	check = token;
	prev = NULL;
	while (check != NULL)
	{
		if (is_logical(check->type))
		{
			if (prev == NULL || (!is_cmd(prev->type) && prev->type != PARENTHESIS_R)
				|| check->next == NULL || (!is_cmd(check->next->type) && check->next->type != PARENTHESIS_L))
			{	ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
				ft_putstr_fd(check->content, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (true);
			}
		}
		if (is_redirect(check->type))
		{
			if (check->next != NULL && (is_operator(check->next->type) || is_redirect(check->next->type)))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
				ft_putstr_fd(check->next->content, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (true);
			}
			else if (check->next == NULL || !is_cmd(check->next->type))
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
				return (true);
			}
		}
		if (check->type == PIPE)
		{
			if (prev == NULL || check->next == NULL || !is_cmd(check->next->type))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
				ft_putstr_fd(check->content, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (true);
			}
		}
		prev = check;
		check = check->next;
	}
	return (false);
}
