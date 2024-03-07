/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:46 by mott              #+#    #+#             */
/*   Updated: 2024/03/07 15:49:17 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_words(char *user_input)
{
	int	n_words;

	n_words = 0;
	while (*user_input != '\0')
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		if (*user_input != '\0')
			n_words++;
		while (*user_input != '\0' && ft_isspace(*user_input) == false)
			user_input++;
	}
	return (n_words);
}

static int	count_characters(char *user_input)
{
	int	n_chars;

	n_chars = 0;
	while (*user_input != '\0' && ft_isspace(*user_input) == false)
	{
		n_chars++;
		user_input++;
	}
	return (n_chars);
}

t_token	*tokenizer(char *user_input)
{
	t_token			*token;
	t_token			*new_token;
	int				n_words;
	int				n_chars;
	char			*content;
	int				i;

	n_words = count_words(user_input);
	i = 0;
	token = NULL;
	while (i < n_words)
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		n_chars = count_characters(user_input);
		content = ft_substr(user_input, 0, n_chars);
		if (content == NULL)
			ft_exit();
		// new_token = type??
		new_token = token_new(content);
		if (new_token == NULL)
			ft_exit();
		token_add_back(&token, new_token);
		while (*user_input != '\0' && ft_isspace(*user_input) == false)
			user_input++;
		i++;
	}
	return (token);
}
