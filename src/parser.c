/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 14:20:44 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ms_parser(t_token *tokens, char *user_input)
{
	t_token	*new_token;
	int		n_words;
	int		n_characters;
	char	*content;
	int		i;

	n_words = ms_count_words(user_input);
	i = 0;
	while (i < n_words)
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		n_characters = ms_count_characters(user_input);
		content = ft_substr(user_input, 0, n_characters);
		if (content == NULL)
			ms_exit();
		new_token = ms_new_token(content);
		if (new_token == NULL)
			ms_exit();
		ms_add_back_token(&tokens, new_token);
		while (*user_input != '\0' && ft_isspace(*user_input) == false)
			user_input++;
		i++;
	}
	return (tokens);
}

int	ms_count_words(char *user_input)
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

int	ms_count_characters(char *user_input)
{
	int	n_characters;

	n_characters = 0;
	while (*user_input != '\0' && ft_isspace(*user_input) == false)
	{
		n_characters++;
		user_input++;
	}
	return (n_characters);
}
