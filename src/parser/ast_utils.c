/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:12:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 20:41:20 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_command_group(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current != NULL)
	{
		if (current->type != COMMAND)
			break ;
		count++;
		current = current->next;
	}
	return (count);
}

char	**token_to_str_array(t_token *tokens)
{
	char	**argv;
	int		n_tokens;
	int		i;

	n_tokens = count_command_group(tokens);
	argv = (char **)ft_calloc(n_tokens + 1, sizeof(char *));
	if (argv == NULL)
		ft_exit("malloc");
	i = 0;
	while (tokens != NULL && i < n_tokens)
	{
		argv[i] = ft_strdup(tokens->content);
		if (argv[i] == NULL)
		{
			while (i-- > 0)
				free(argv[i]);
			free(argv);
			ft_exit("malloc");
		}
		tokens = tokens->next;
		i++;
	}
	argv[i] = NULL;
	// print_char_array(argv);
	return (argv);
}

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*node;

	node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!node)
		ft_exit("malloc");
	node->type = token->type;
	node->left = NULL;
	node->right = NULL;
	if (token->type == COMMAND)
	node->argv = token_to_str_array(token);
	else
		node->argv = NULL;
	return (node);
}
