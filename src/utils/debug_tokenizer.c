/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:59:42 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/13 16:15:21 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static const char *token_type_to_string(t_token_type type)
{
	switch(type)
	{
		case UNKNOWN:
			return "UNKNOWN";
		case WORD:
			return "WORD";
		case SINGLE_QUOTE:
			return "SINGLE_QUOTE";
		case DOUBLE_QUOTE:
			return "DOUBLE_QUOTE";
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
		ft_printf("%s\n", current_token->content);
		ft_printf("%s\n", token_type_to_string(current_token->type));
		ft_printf("-----------\n");
		i++;
		current_token = current_token->next; 
	}
}
