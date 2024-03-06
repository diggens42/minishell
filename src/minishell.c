/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 13:15:17 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	ms_interactive_mode(env);
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}

void	ms_interactive_mode(t_env *env)
{
	char	*user_input;
	char	*user_input2;
	char	*temp;
	t_token	*tokens;

	while (true)
	{
		user_input = readline(PROMPT_STD);
		add_history(user_input);
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue ;
		}
		while (user_input[ft_strlen(user_input) - 1] == '\\')
		{
			user_input[ft_strlen(user_input) - 1] = '\0';
			user_input2 = readline(PROMPT_MULTI_LINE);
			//consider also checking for NULL return from readline to handle EOF (Ctrl+D)
			temp = user_input;
			user_input = ft_strjoin(user_input, user_input2);
			free (temp);
			free (user_input2);
		}
		// if (user_input == '<<')
		// 	continue ;
		tokens = NULL;
		tokens = ms_parser(tokens, user_input);
		if (tokens == NULL)
			ms_exit();
		ms_execute(tokens, env);
		free(user_input);
		ms_free_token_list(tokens);
	}
}

void	ms_exit(void)
{
	// system("leaks minishell");
	exit(EXIT_SUCCESS);
}

void	ms_free_token_list(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = temp;
	}
}
