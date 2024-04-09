/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:53:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/09 16:06:00 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	syntax_logical(t_token *prev, t_token *check)
{
	if (prev == NULL || (!is_cmd(prev->type) && prev->type != PARENTHESIS_R)
		|| check->next == NULL
		||(!is_cmd(check->next->type) && check->next->type != PARENTHESIS_L))
	{
		ft_perror_3(check->content);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	syntax_redirect(t_token *check)
{
	if (check->next != NULL && check->next->type == WILDCARD)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (check->next != NULL && (is_operator(check->next->type)
		|| is_redirect(check->next->type)))
	{
		ft_perror_3(check->next->content);
		return (2);
	}
	else if (check->next == NULL || (!is_cmd(check->next->type)
			&& !is_redirect(check->next->type)))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	syntax_pipe(t_token *prev, t_token *check)
{
	if (prev == NULL || check->next == NULL || (!is_cmd(check->next->type)
		&& !is_redirect(check->next->type) && !is_logical(check->next->type)))
	{
		ft_perror_3(check->content);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	syntax_parenthesis(t_token *prev, t_token *check)
{
	if (check->type == PARENTHESIS_L)
	{
		if (prev != NULL && !is_logical(prev->type))
		{
			ft_putstr_fd("read the subject\n", STDERR_FILENO);
			return (2);
		}
	}
	if (check->type == PARENTHESIS_R)
	{
		if (check->next != NULL && !is_logical(check->next->type))
		{
			ft_perror_3(check->content);
			return (2);
		}
	}
	return (EXIT_SUCCESS);
}

int	operator_syntax(t_token *token)
{
	t_token *check;
	t_token *prev;
	int		exit_status;

	check = token;
	prev = NULL;
	exit_status = EXIT_SUCCESS;
	while (check != NULL)
	{
		if (is_logical(check->type))
			exit_status = syntax_logical(prev, check);
		if (is_redirect(check->type))
			exit_status = syntax_redirect(check);
		if (check->type == PIPE)
			exit_status = syntax_pipe(prev, check);
		if (is_parenthesis(check->type))
			exit_status = syntax_parenthesis(prev, check);
		if (exit_status != EXIT_SUCCESS)
			return (exit_status);
		prev = check;
		check = check->next;
	}
	return (exit_status);
}

int	parenthesis_syntax(t_token *token)
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
			return (2);
		}
		check = check->next;
	}
	if (parenthesis > 0)
	{
		ft_putstr_fd("unclosed parenthesis\n", STDERR_FILENO);
		return (2);
	}
	return (EXIT_SUCCESS);
}
