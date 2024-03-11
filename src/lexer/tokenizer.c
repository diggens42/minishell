/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/11 18:11:53 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_chars_and_symbols(char *user_input)
{
	int	n_chars;

	n_chars = is_multi_special_char(user_input);
	if (n_chars > 0)
		return (n_chars);
	if (user_input[0] == '$')
	{
		if (user_input[1] == '?' || user_input[1] == '$')
			return (2);
		n_chars++;
		while (user_input[n_chars] != '\0' && !ft_isspace(user_input[n_chars])
				&& is_variable_char(user_input[n_chars]))
			n_chars++;
		if (n_chars == 1)
			return (1);
		return(n_chars);
	}
	else if (is_special_char(user_input[0]))
		return (1);
	while (user_input[n_chars] != '\0' && !ft_isspace(user_input[n_chars])
			&& !is_special_char(user_input[n_chars]))
		n_chars++;
	return (n_chars);
}

t_token	*tokenizer(char *user_input, t_env *env)
{
	t_token	*token_head;
	t_token	*token_next;
	int		n_chars;

	token_head = NULL;
	while (*user_input != '\0')
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		n_chars = count_chars_and_symbols(user_input);
		if (*user_input == '\0')
			break ;
		token_next = token_new();
		if (!token_next)
			ft_exit();
		token_next->content = ft_substr(user_input, 0, n_chars);
		token_next->length = n_chars;
		token_next->type = set_token_type(token_next->content, token_next->length);
		token_add_back(&token_head, token_next);
		user_input += n_chars;
	}
	// check_tokens(token_head);
	resolve_tokens(&token_head, env);
	// check_tokens(token_head);
	return (token_head);
}
