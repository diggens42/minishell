/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:12:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/10 17:12:16 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	count_word_group(t_token *tokens)
{
	t_token	*current;
	int		count;
	
	current = tokens;
	count = 0;
	while (current != NULL)
	{
		if (current->type != WORD)
			break ;
		count++;
		current->used = true;
		current = current->next;
	}
	return (count);
}

char	**tokens_to_char_array2(t_token *tokens)
{
	t_token	*current;
	char	**argv;
	int		n_tokens;
	int		i;

	current = tokens;
	n_tokens = count_word_group(tokens);
	argv = (char **)malloc(sizeof(char *) * (n_tokens + 1));
	if (argv == NULL)
		ft_exit(); //TODO handle malloc failure
	i = -1;
	while (current != NULL && ++i < n_tokens)
	{
		argv[i] = ft_strdup(current->content);
		if (argv[i] == NULL)
		{
			while (i-- > 0)
				free(argv[i]);
			free(argv);
			ft_exit();//TODO handle ft_strdup failure
		}
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_ast_node	*build_ast_simple(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*last_root;
	t_ast_node	*cmd_node;
	t_ast_node	*pipe_node;
	t_ast_node	*last_node;
	
	root = NULL;
	last_root = NULL;
	last_node = NULL;
	while (tokens != NULL)
	{
		if (tokens->type == WORD)
		{
			cmd_node = create_ast_node(tokens);
			while (tokens != NULL && tokens->type == WORD)
				tokens = tokens->next;
			if (!root)
				root = cmd_node;
			else if (last_node && last_node->type == PIPE)
			{
				last_node->right = cmd_node;
				cmd_node->top = last_node;
			}
			// TODO else - more logic for more complex structures
			last_node = cmd_node;
		}
		else if (tokens->type == PIPE)
		{
			pipe_node = create_ast_node(tokens);
			if (!root)
				ft_exit(); //TODO handle error PIPE with no preceding command
			last_root = root;
			pipe_node->left = last_root;
			if (last_root)
				last_root->top = pipe_node;
			root = pipe_node;
			last_node = pipe_node;
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (root);
}

t_ast_node	*create_ast_node(t_token *token)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);//TODO handle malloc error
	node->type = token->type;
	node->left = NULL;
	node->right = NULL;
	node->top = NULL;
	if (token->type == WORD)
		node->argv = tokens_to_char_array2(token);
	else
		node->argv = NULL;
	if (token->used == false)
		token->used = true;
	return (node);
}
