/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:20:32 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 14:59:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token_type	set_token_type(char	*content)
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
	else if (ft_strchr(content, '*') != NULL)
		return (WILDCARD);
	else if (ft_strcmp(content, "$") == 0)//TODO
		return (DOLLAR);
	else if (ft_strcmp(content, "$\"") == 0)//TODO
		return (DOLLAR_QUOTE);
	else if (content[0] == '\'' && content[ft_strlen(content) - 1] == '\'')
		return (SINGLE_QUOTE);	
	else if (content[0] == '"' && content[ft_strlen(content) - 1] == '"')
		return (DOUBLE_QUOTE);
	else
		return (WORD);
}


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
	t_token	*token;
	t_token	*new_token;
	char	*content;
	int		n_chars;
	
	token = NULL;
	new_token = NULL;
	while (*user_input != '\0')
	{
		while (ft_isspace(*user_input) == true)
			user_input++;
		if (*user_input == '\0')
			break ;
		n_chars = count_chars_and_symbols(user_input);
		content = ft_substr(user_input, 0, n_chars);
		if (!content)
			ft_exit();
		new_token = token_new(content);
		if (!new_token)
			ft_exit();
		new_token->type = set_token_type(new_token->content);
		token_add_back(&token, new_token);
		user_input += n_chars;
	}
	return (token);
}

// static int	ms_count_words(char *user_input)
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

// t_token	*tokenizer(char *user_input)
// {
// 	t_token			*token;
// 	t_token			*new_token;
// 	// int				n_words;
// 	int				n_chars;
// 	char			*content;
// 	int				i;

// 	// n_words = count_words(user_input);
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
// 		new_token = token_new(content);
// 		new_token->type = set_token_type(new_token->content);
// 		if (new_token == NULL)
// 			ft_exit();
// 		token_add_back(&token, new_token);
// 		while (*user_input != '\0' && ft_isspace(*user_input) == false)
// 			user_input++;
// 		i++;
// 	}
// 	return (token);
// }
