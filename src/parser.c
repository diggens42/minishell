/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:38:23 by mott              #+#    #+#             */
/*   Updated: 2024/03/01 20:08:53 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_count_words(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (*str != '\0')
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		if (*str != '\0')
			i++;
		while (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\0')
			str++;
	}
	return (i);
}

int	ms_count_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

t_token	*ms_parser(char *user_input)
{
	t_token	*tokens;
	t_token	*new_token;
	int		words;
	int		characters;
	char	*content;
	int		i;

	words = ms_count_words(user_input);
	tokens = NULL;
	// tokens = malloc(sizeof(t_token *) * (words + 1));
	// if (tokens == NULL)
	// 	return (NULL);
	i = 0;
	while (i < words)
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		characters = ms_count_characters(user_input);
		content = ft_substr(user_input, 0, characters);
		//error
		new_token = ms_new_token(content);
		// error
		ms_token_add_back(&tokens, new_token);
		while (*user_input != '\0' && ft_isspace(*user_input) == false)
			user_input++;
		i++;
	}
	return (tokens);
}

// TODO
// malloc content with malloc?
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

