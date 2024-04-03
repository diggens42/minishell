/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:12:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/03 16:38:31 by fwahl            ###   ########.fr       */
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

// char	**token_to_str_array(t_token *tokens)
// {
// 	char	**argv;
// 	int		n_tokens;
// 	int		i;

// 	n_tokens = count_command_group(tokens);
// 	argv = (char **)ft_calloc(n_tokens + 1, sizeof(char *));
// 	if (argv == NULL)
// 		ft_exit("malloc");
// 	i = 0;
// 	while (tokens != NULL && i < n_tokens)
// 	{
// 		argv[i] = ft_strdup(tokens->content);
// 		if (argv[i] == NULL)
// 		{
// 			while (i-- > 0)
// 				free(argv[i]);
// 			free(argv);
// 			ft_exit("malloc");
// 		}
// 		tokens = tokens->next;
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	// print_char_array(argv);
// 	return (argv);
// }

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*node;
	int		i;

	node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!node)
		ft_exit("malloc");
	node->type = token->type;
	if (is_cmd(token->type) || is_redirect(token->type))
	{
		node->type = COMMAND;
		node->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		node->cmd->argv = (char **)ft_calloc(n_cmd(token) + 1, sizeof(char *));
		// if (is_redirect(token->type))
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
