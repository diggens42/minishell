/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/07 20:26:04 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	operator_syntax(t_token *token)
{
	t_token *check;
	t_token *prev;
	int		parenthesis;

	parenthesis = 0;
	check = token;
	prev = NULL;
	while (check != NULL)
	{
		if (is_logical(check->type))
		{
			if (prev == NULL || (!is_cmd(prev->type) && prev->type != PARENTHESIS_R)
				|| check->next == NULL || (!is_cmd(check->next->type) && check->next->type != PARENTHESIS_L))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
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
			if (prev == NULL || check->next == NULL || (!is_cmd(check->next->type) && !is_redirect(check->next->type)))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
				ft_putstr_fd(check->content, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (true);
			}
		}
		if (check->type == PARENTHESIS_L || check->type == PARENTHESIS_R)
		{
			if (check->type == PARENTHESIS_L)
			{
				if (prev != NULL && !is_logical(prev->type))
				{
					ft_putstr_fd("read the subject\n", STDERR_FILENO);
					return (true);
				}
				parenthesis++;
			}
			if (check->type == PARENTHESIS_R)
			{
				if (check->next != NULL && !is_logical(check->next->type))
				{
					ft_putstr_fd("read the subject\n", STDERR_FILENO);
					return (true);
				}
				parenthesis--;
			}
			if (parenthesis < 0)
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
	if (parenthesis > 0)
	{
		ft_putstr_fd("unclosed parenthesis\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}
