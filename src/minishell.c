/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/08 13:24:43 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	interactive_mode(env);
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}

void	interactive_mode(t_env *env)
{
	char		*user_input;
	char		*user_input2;
	char		*temp;
	t_token		*tokens;
	t_command	*commands;

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

		tokens = tokenizer(user_input);
		commands = command_parser(tokens);
		execute(commands, env);
		free(user_input);
		// free commands + tokens
	}
}
