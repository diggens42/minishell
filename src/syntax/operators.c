/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/08 21:31:33 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	syntax_logical(t_token *prev, t_token *check)
{
	if (prev == NULL || (!is_cmd(prev->type) && prev->type != PARENTHESIS_R)
		|| check->next == NULL
		||(!is_cmd(check->next->type) && check->next->type != PARENTHESIS_L))
	{
		ft_perror_3(check->content);
		return (true);
	}
	return (false);
}

static bool	syntax_redirect(t_token *check)
{
	if (check->next != NULL && check->next->type == WILDCARD)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (true);
	}
	if (check->next != NULL && (is_operator(check->next->type)
		|| is_redirect(check->next->type)))
	{
		ft_perror_3(check->content);
		return (true);
	}
	else if (check->next == NULL || (!is_cmd(check->next->type)
			&& !is_redirect(check->next->type)))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static bool	syntax_pipe(t_token *prev, t_token *check)
{
	if (prev == NULL || check->next == NULL || (!is_cmd(check->next->type)
		&& !is_redirect(check->next->type) && !is_logical(check->next->type)))
	{
		ft_perror_3(check->content);
		return (true);
	}
	return (false);
}

static bool	syntax_parenthesis(t_token *prev, t_token *check)
{
	if (check->type == PARENTHESIS_L)
	{
		if (prev != NULL && !is_logical(prev->type))
		{
			ft_putstr_fd("read the subject\n", STDERR_FILENO);
			return (true);
		}
	}
	if (check->type == PARENTHESIS_R)
	{
		if (check->next != NULL && !is_logical(check->next->type))
		{
			ft_perror_3(check->content);
			return (true);
		}
	}
	return (false);
}

bool	operator_syntax(t_token *token)
{
	t_token *check;
	t_token *prev;

	check = token;
	prev = NULL;
	while (check != NULL)
	{
		if (is_logical(check->type) && syntax_logical(prev, check))
			return (true);
		if (is_redirect(check->type) && syntax_redirect(check))
			return (true);
		if (check->type == PIPE && syntax_pipe(prev, check))
			return (true);
		if (is_parenthesis(check->type) && syntax_parenthesis(prev, check))
			return (true);
		prev = check;
		check = check->next;
	}
	return (false);
}

bool	parenthesis_syntax(t_token *token)
{
	t_token	*check;
	int		parenthesis;

	check = token;
	parenthesis = 0;
	while (check != NULL)
	{
		if (check->type == PARENTHESIS_L)
			parenthesis++;
		if (check->type == PARENTHESIS_R)
			parenthesis--;
		if (parenthesis < 0)
		{
			ft_perror_3(check->content);
			return (true);
		}
		check = check->next;
	}
	if (parenthesis > 0)
	{
		ft_putstr_fd("unclosed parenthesis\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}
