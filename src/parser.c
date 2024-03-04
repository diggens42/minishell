/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:38:23 by mott              #+#    #+#             */
/*   Updated: 2024/03/03 19:48:28 by mott             ###   ########.fr       */
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
		ms_token_add_back(&tokens, new_token);
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

t_token	*ms_new_token(char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

t_token	*ms_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	ms_token_add_back(t_token **token, t_token *new_token)
{
	t_token	*last_token;

	if (*token == NULL)
		*token = new_token;
	else
	{
		last_token = ms_last_token(*token);
		last_token->next = new_token;
	}
}

void ms_print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		ft_printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}
