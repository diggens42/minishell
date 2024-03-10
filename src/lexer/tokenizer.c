/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/10 17:44:11 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_chars_and_symbols(char *user_input)
{
	int	n_chars;

	n_chars = is_multi_special_char(user_input);
	if (n_chars > 0)
		return (n_chars);
	if (is_special_char(user_input[0]))
		return (1);
	while (user_input[n_chars] != '\0' && ft_isspace(user_input[n_chars]) == false
			&& is_special_char(user_input[n_chars]) == false)
		n_chars++;
	return (n_chars);
}

t_token	*tokenizer(char *user_input)
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
	check_tokens(token_head);
	return (token_head);
}

// static int	count_words(char *user_input)
// {
// 	int	n_words;

// 	n_words = 0;
// 	while (*user_input != '\0')
// 	{
// 		while (ft_isspace(*user_input) == true)
// 			user_input++;
// 		if (*user_input != '\0')
// 			n_words++;
// 		while (*user_input != '\0' && ft_isspace(*user_input) == false)
// 			user_input++;
// 	}
// 	return (n_words);
// }

// static int	count_characters(char *user_input)
// {
// 	int	n_chars;

// 	n_chars = 0;
// 	while (*user_input != '\0' && ft_isspace(*user_input) == false)
// 	{
// 		n_chars++;
// 		user_input++;
// 	}
// 	return (n_chars);
// }

// t_token	*tokenizer(char *user_input)
// {
// 	t_token			*token;
// 	t_token			*new_token;
// 	int				n_words;
// 	int				n_chars;
// 	char			*content;
// 	int				i;

// 	n_words = count_words(user_input);
// 	i = 0;
// 	token = NULL;
// 	while (i < n_words)
// 	{
// 		while (ft_isspace(*user_input) == true)
// 			user_input++;
// 		n_chars = count_characters(user_input);
// 		content = ft_substr(user_input, 0, n_chars);
// 		if (content == NULL)
// 			ft_exit();
// 		new_token = token_new();
// 		new_token->content = user_input;
// 		new_token->length = n_chars;
// 		new_token->type = set_token_type(new_token->content, new_token->length);
// 		if (new_token == NULL)
// 			ft_exit();
// 		token_add_back(&token, new_token);
// 		while (*user_input != '\0' && ft_isspace(*user_input) == false)
// 			user_input++;
// 		i++;
// 	}
// 	return (token);
// }
