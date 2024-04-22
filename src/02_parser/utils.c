/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:12:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 21:25:30 by mott             ###   ########.fr       */
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

static int	n_red(t_token *tokens)
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

static t_cmd	*new_cmd_node(t_token *token)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		ft_perror("malloc", strerror(errno));
	cmd->argv = ft_calloc(n_cmd(token) + 1, sizeof(char *));
	cmd->type = ft_calloc(n_cmd(token) + 1, sizeof(t_type *));
	i = 0;
	while (i < n_cmd(token))
	{
		cmd->type[i] = ft_calloc(1, sizeof(t_type));
		i++;
	}
	cmd->redir = ft_calloc(n_red(token) + 1, sizeof(t_redir *));
	i = 0;
	while (i < n_red(token))
	{
		cmd->redir[i] = ft_calloc(1, sizeof(t_redir));
		i++;
	}
	return (cmd);
}

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		ft_perror("malloc", strerror(errno));
	node->type = token->type;
	if (is_cmd(token->type) || is_redirect(token->type))
	{
		node->type = COMMAND;
		node->cmd = new_cmd_node(token);
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
