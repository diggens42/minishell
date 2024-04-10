/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:14:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/09 18:13:24 by mott             ###   ########.fr       */
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
			return(cmd_node);
		if (is_redirect((*token)->type))
		{
			cmd_node->cmd->redir[i]->type = (*token)->type;
			advance_and_free_token(token);
			cmd_node->cmd->redir[i]->file = ft_strdup((*token)->content);
			advance_and_free_token(token);
			i++;
		}
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

static t_ast	*ast_parenthesis(t_token **token)
{
	t_ast	*subtree;

	subtree = NULL;
	if (*token == NULL || (*token)->type != PARENTHESIS_L)
		return (NULL);
	advance_and_free_token(token);
	subtree = ast_parser(token);
	subtree->subshell = true;
	if (*token == NULL || (*token)->type != PARENTHESIS_R)
		return (NULL); //TODO handle unclosed parenthesis
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

static t_ast	*ast_logical(t_token **token, t_ast *left)
{
	t_ast	*node;
	t_ast	*logical;
	t_ast	*cmd_node;

	node = left;
	while (*token != NULL && is_logical((*token)->type))
	{
		logical = new_ast_node(*token);
		logical->left = node;
		advance_and_free_token(token);
		if (*token != NULL && (*token)->type == PARENTHESIS_L)
			logical->right = ast_parenthesis(token);
		cmd_node = ast_cmd(token);
		// if (*token != NULL && (*token)->type == PARENTHESIS_L)
		// 	logical->right = ast_parenthesis(token);
		if (*token != NULL && (*token)->type == PIPE)
			logical->right = ast_pipe(token, cmd_node);
		else
			logical->right = cmd_node;
		node = logical;
		if (*token == NULL || !is_logical((*token)->type))
			break ;
	}
	return (node);
}

t_ast	*ast_parser(t_token **token)
{
	t_ast	*node;

	node = NULL;
	if (token == NULL || (*token) == NULL)
		return (NULL);
	while (*token != NULL)
	{
		if ((*token)->type == PARENTHESIS_L)
			node = ast_parenthesis(token);
		else if (*token != NULL && (is_cmd((*token)->type) || is_redirect((*token)->type)))
			node = ast_cmd(token);
		else if (*token != NULL && (*token)->type == PIPE)
			node = ast_pipe(token, node);
		else if (*token != NULL && (is_logical((*token)->type)))
			node = ast_logical(token, node);
		else if (*token != NULL && (*token)->type == PARENTHESIS_R)
			return(node);
	}
	return (node);
}
