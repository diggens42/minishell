/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:54:18 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/27 15:46:02 by mott             ###   ########.fr       */
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

void print_ast(t_ast* node, int level) {
    if (node == NULL) return;

    // Print indentation based on the level of depth in the tree.
    for (int i = 0; i < level; ++i) {
        // printf("  "); // Two spaces per level of depth.
        fprintf(stderr, "  "); // Two spaces per level of depth.
    }

    // Print the current node.
    // printf("%s", token_type_to_string(node->type));
	fprintf(stderr, "\x1b[34m%s\x1b[0m", token_type_to_string(node->type));
    if (node->type == COMMAND) {
        // printf(": %s", node->argv[0]); // Assuming argv[0] is the command name.
		fprintf(stderr, "\x1b[34m: %s\x1b[0m", node->cmd->argv[0]);
    }
    printf("\n");

    // Recursively print the left and right children, increasing the level of depth.
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}
