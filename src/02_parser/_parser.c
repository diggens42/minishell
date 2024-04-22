/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:14:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/22 21:30:01 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*ast_cmd(t_token **token)
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
		if (*token != NULL && (*token)->type == PARENTHESIS_R)
			return (cmd_node);
		if (is_redirect((*token)->type))
			ast_redirect(cmd_node, token, &i);
		if (*token != NULL && is_cmd((*token)->type))
		{
			cmd_node->cmd->argv[j] = ft_strdup((*token)->content);
			*(cmd_node->cmd->type[j]) = (*token)->type;
			advance_and_free_token(token);
			j++;
		}
	}
	return (cmd_node);
}

static t_ast	*ast_parenthesis(t_mini *mini, t_token **token)
{
	t_ast	*subtree;

	subtree = NULL;
	if (*token == NULL || (*token)->type != PARENTHESIS_L)
		return (NULL);
	advance_and_free_token(token);
	subtree = ast_parser(mini, token);
	subtree->subshell = true;
	if (*token == NULL || (*token)->type != PARENTHESIS_R)
		return (NULL);
	advance_and_free_token(token);
	return (subtree);
}

static t_ast	*ast_pipe(t_token **token, t_ast *left)
{
	t_ast	*pipe;

	while (*token != NULL && (*token)->type == PIPE)
	{
		pipe = new_ast_node(*token);
		pipe->left = left;
		advance_and_free_token(token);
		pipe->right = ast_cmd(token);
		left = pipe;
	}
	return (left);
}

static t_ast	*ast_logical(t_mini *mini, t_token **token, t_ast *left)
{
	t_ast	*node;
	t_ast	*logical;
	t_ast	*right;

	node = left;
	while (*token != NULL && is_logical((*token)->type))
	{
		logical = new_ast_node(*token);
		logical->left = node;
		advance_and_free_token(token);
		if (*token != NULL && (*token)->type == PARENTHESIS_L)
			right = ast_parenthesis(mini, token);
		else
			right = ast_cmd(token);
		if (*token != NULL && (*token)->type == PIPE)
			right = ast_pipe(token, right);
		logical->right = right;
		node = logical;
	}
	return (node);
}

t_ast	*ast_parser(t_mini *mini, t_token **token)
{
	t_ast	*node;

	node = NULL;
	if (token == NULL || (*token) == NULL)
		return (NULL);
	while (*token != NULL)
	{
		if ((*token)->type == PARENTHESIS_L)
			node = ast_parenthesis(mini, token);
		else if (*token != NULL && (is_cmd((*token)->type)
				|| is_redirect((*token)->type)))
			node = ast_cmd(token);
		else if (*token != NULL && (*token)->type == PIPE)
			node = ast_pipe(token, node);
		else if (*token != NULL && (is_logical((*token)->type)))
			node = ast_logical(mini, token, node);
		else if (*token != NULL && (*token)->type == PARENTHESIS_R)
			return (node);
	}
	return (node);
}
