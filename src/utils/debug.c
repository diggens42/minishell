/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:24:11 by mott              #+#    #+#             */
/*   Updated: 2024/04/10 19:28:54 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_print(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		ft_printf("token[%d]: %s - %p\n", i, tokens->content, tokens->content);
		i++;
		tokens = tokens->next;
	}
}

void	print_char_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_printf("str[%d]: %s\n", i, str[i]);
		i++;
	}
}

static const char *token_type_to_string2(t_type type)
{
	switch(type)
	{
		case UNKNOWN:
			return "UNKNOWN";
		case COMMAND:
			return "COMMAND";
		case SINGLE_QUOTE:
			return "SINGLE_QUOTE";
		case REDIR_IN:
			return "REDIR_IN";
		case REDIR_HEREDOC:
			return "REDIR_HEREDOC";
		case REDIR_OUT:
			return "REDIR_OUT";
		case REDIR_APPEND:
			return "REDIR_APPEND";
		case PIPE:
			return "PIPE";
		case DOLLAR:
			return "DOLLAR";
		case DQMARK:
			return "DQMARK";
		case AND:
			return "AND";
		case OR:
			return "OR";
		case PARENTHESIS_L:
			return "PARENTHESIS_L";
		case PARENTHESIS_R:
			return "PARENTHESIS_R";
		case WILDCARD:
			return "WILDCARD";
		default:
			return "INVALID TYPE";
	}
}

void	check_tokens(t_token *tokens)
{
	t_token *current_token;
	int		i;

	current_token = tokens;
	i = 1;
	while (current_token != NULL)
	{
		ft_printf("Token: %d\n", i);
		ft_printf("Length: %d\n", current_token->length);
		ft_printf("%s\n", current_token->content);
		ft_printf("%s\n", token_type_to_string2(current_token->type));
		ft_printf("-----------\n");
		i++;
		current_token = current_token->next;
	}
}

char	*token_type_to_string(t_type type)
{
    switch (type) {
        case COMMAND: return "COMMAND";
        case PIPE: return "PIPE";
        case AND: return "AND";
        case OR: return "OR";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_HEREDOC: return "REDIR_HEREDOC";
		case REDIR_OUT: return "REDIR_OUT";
		case REDIR_APPEND : return "REDIR_APPEND";
		case DOLLAR : return "DOLLAR";
		case DQMARK : return "DQMARK";
		case SINGLE_QUOTE : return "SQUOTE";
		case WILDCARD:	return "WILDCARD";
        // Add other cases as necessary.
        default: return "UNKNOWN";
    }
}

void print_ast(t_ast* node, int level)
{
	int j = 0;
	int k = 0;
    if (node == NULL) return;

    // Print indentation based on the level of depth in the tree.
    for (int i = 0; i < level; ++i) {
        // printf("  "); // Two spaces per level of depth.
        fprintf(stderr, "  "); // Two spaces per level of depth.
    }

	fprintf(stderr, "\x1b[34m%s:\x1b[0m", token_type_to_string(node->type));
    if (node->type == COMMAND)
	{
		while (node->cmd->argv[j] != NULL)
		{
			fprintf(stderr, "\x1b[34m argv[%d]: %s\x1b[0m", j, node->cmd->argv[j]);
			j++;
		}
		if (node->cmd->redir != NULL)
		{
			while (node->cmd->redir[k] != NULL)
			{
				fprintf(stderr, "\x1b[34m    %s:\x1b[0m", token_type_to_string(node->cmd->redir[k]->type));
				fprintf(stderr, "\x1b[34m    %s\x1b[0m", node->cmd->redir[k]->file);
				k++;
			}

		}
    }
    printf("\n");

    // Recursively print the left and right children, increasing the level of depth.
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}
