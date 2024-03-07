/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/parser.c
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 18:38:18 by fwahl            ###   ########.fr       */
=======
/*   Created: 2024/03/07 15:36:46 by mott              #+#    #+#             */
/*   Updated: 2024/03/07 15:49:17 by mott             ###   ########.fr       */
>>>>>>> main:src/parser/tokenizer.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD:src/parser.c
t_token	*ms_parser(t_token *tokens, char *user_input)
{
	t_token			*new_token;
	t_token_type	type;
	char			*content;
	int				n_words;
	int				n_characters;
	int				i;

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
		type = set_token_type(content);
		new_token->type = type;
		ms_add_back_token(&tokens, new_token);
		while (*user_input != '\0' && ft_isspace(*user_input) == false)
			user_input++;
		i++;
	}
	return (tokens);
}

t_token_type	set_token_type(char	*content)
{
	if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(content, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(content, "<<") == 0)
		return (REDIRECT_HERE_DOC);
	else if (ft_strcmp(content, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(content, ">>") == 0)
		return (REDIRECT_APPEND);
	else if (ft_strcmp(content, "&&") == 0)
		return (AND);
	else if (ft_strcmp(content, "||") == 0)
		return (OR);
	else if (ft_strcmp(content, "*") == 0)
		return (WILDCARD);
	else if (ft_strcmp(content, "$") == 0)
		return (DOLLAR);
	else if (ft_strcmp(content, "$\"") == 0)
		return (DOLLAR_QUOTE);
	//TODO QUOTES
	else
		return (WORD);
}

int	ms_count_words(char *user_input)
=======
static int	count_words(char *user_input)
>>>>>>> main:src/parser/tokenizer.c
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
