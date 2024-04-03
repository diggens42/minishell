/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:54:18 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/03 19:12:43 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			fprintf(stderr, "\x1b[34m %s\x1b[0m", node->cmd->argv[j]);
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
