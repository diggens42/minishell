/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:12:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/06 15:25:15 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	n_cmd(t_token *tokens)
{
	t_token	*current;
	int		n_cmd;

	current = tokens;
	n_cmd = 0;
	while (current != NULL)
	{
		if (is_operator(current->type))
			break ;
		if (is_cmd(current->type))
			n_cmd++;
		current = current->next;
	}
	return (n_cmd);
}

static int n_red(t_token *tokens)
{
	t_token	*current;
	int		n_red;

	current = tokens;
	n_red = 0;
	while (current != NULL)
	{
		if (is_operator(current->type))
			break ;
		if (is_redirect(current->type))
			n_red++;
		current = current->next;
	}
	return (n_red);
}

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*node;
	int		i;

	node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!node)
		ft_perror("malloc", strerror(errno));
	node->type = token->type;
	if (is_cmd(token->type) || is_redirect(token->type))
	{
		node->type = COMMAND;
		node->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		node->cmd->argv = (char **)ft_calloc(n_cmd(token) + 1, sizeof(char *));
		node->cmd->type = (t_type **)ft_calloc(n_cmd(token) + 1, sizeof(t_type *));
		i = 0;
		while (i < n_cmd(token))
		{
			node->cmd->type[i] = (t_type *)ft_calloc(1, sizeof(t_type));
			i++;
		}
		node->cmd->redir = (t_redir **)ft_calloc(n_red(token) + 1, sizeof(t_redir *));
		i = 0;
		while (i < n_red(token))
		{
			node->cmd->redir[i] = (t_redir *)ft_calloc(1, sizeof(t_redir));
			i++;
		}
	}
	return (node);
}

void	advance_and_free_token(t_token **token)
{
	t_token	*next_token;

	if (token == NULL || *token == NULL)
		return ;
	next_token = (*token)->next;
	if (*token)
	{
		free((*token)->content);
		free(*token);
	}
	*token = next_token;
}

