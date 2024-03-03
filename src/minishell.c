/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/03 17:08:47 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	ms_interactive_mode(envp);
	system("leaks minishell");
	return (EXIT_SUCCESS);
}

// TODO
// Multi line commands '\'
// heredoc detector '<<'
void	ms_interactive_mode(char **envp)
{
	char	*user_input;
	t_token	*tokens;
	// int	i;
	// char	*temp;

	while (true)
	{
		user_input = readline(PROMPT_STD);
		add_history(user_input);

		tokens = ms_parser(user_input);
			// if (tokens == NULL)
			// 	return;
			// ft_putchar_fd('X', STDERR_FILENO);
			ms_execute_builtins(tokens, envp);
			// ms_execute_commands(tokens);
			// ft_putchar_fd('X', STDERR_FILENO);
			// if (ft_strncmp(user_input, "ls", 3) == 0)
			// 	ms_executor(tokens);

			// i = 0;
			// ft_putchar_fd('X', STDERR_FILENO);
			// while (tokens != NULL)
			// {
			// 	ft_printf("i: %d, %s\n", i, tokens->content);
			// 	tokens = tokens->next;
			// 	i++;
			// }
		// }
		free(user_input);
	}
	// while (ft_strncmp(line, "exit\n", 6) != 0)
	// {
	// 	ms_print_prompt(PROMPT_STD);
	// 	line = get_next_line(STDIN_FILENO);
	// 	if (line == NULL)
	// 		exit(EXIT_FAILURE);
	// 	else if (line[0] == '\n')
	// 		continue ;
	// 	else if (line[ft_strlen(line) - 2] == '\\')
	// 	{
	// 		ms_print_prompt(PROMPT_MULTI_LINE);
	// 		temp = line;
	// 		temp[ft_strlen(temp) - 2] = '\0';
	// 		line = get_next_line(STDIN_FILENO);
	// 		line = ft_strjoin(temp, line);
	// 		free(temp);
	// 	}
	// 	else if (ft_strncmp(line, "exit\n", 6) == 0)
	// 	{
	// 		free(line);
	// 		return ;
	// 	}
	// 	ft_printf("-> %s", line);
	// 	free(line);
	// }
}

// char	*ms_read_user_input(void)
// {

// }

// void	ms_print_prompt(int prompt)
// {
// 	if (prompt == PROMPT_STD)
// 		ft_putstr_fd("% ", STDOUT_FILENO);
// 	else if (prompt == PROMPT_MULTI_LINE)
// 		ft_putstr_fd("> ", STDOUT_FILENO);
// 	else if (prompt == PROMPT_HEREDOC)
// 		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
// }
