/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/12 17:08:39 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenizer(char *user_input, t_env *env)
{
	t_token	*token_head;
	t_token	*token;

	token_head = NULL;
	while (*user_input != '\0')
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		if (*user_input == '\0')
			break ;
		token = token_new();
		if (!token)
			ft_exit();
		token->length = set_token_length(user_input);
		token->content = ft_substr(user_input, 0, token->length);
		token->type = set_token_type(token->content, token->length);
		token_add_back(&token_head, token);
		user_input += token->length;
	}
	// check_tokens(token_head);
	process_token_content(&token_head, env);
	// check_tokens(token_head);
	return (token_head);
}
