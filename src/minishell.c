/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/01 19:19:46 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TODO
// main() with char **envp or function getenv()?
int	main(void)
{
	ms_interactive_mode();
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}

// TODO
// Multi line commands '\'
// heredoc detector '<<'
void	ms_interactive_mode(void)
{
	char	*user_input;
	t_token	*tokens;
	int	i;
	// char	*temp;

	while (true)
	{
		user_input = readline(PROMPT_STD);
		add_history(user_input);
		// ft_printf("%s\n", user_input);
		if (ft_strncmp(user_input, "exit", 5) == 0)
		{
			free(user_input);
			break ;
		}
		else
		{
			tokens = ms_parser(user_input);
			if (ft_strncmp(user_input, "ls", 3) == 0)
				ms_executor(tokens);

			i = 0;
			// ft_putchar_fd('X', STDERR_FILENO);
			while (tokens != NULL)
			{
				ft_printf("i: %d, %s\n", i, tokens->content);
				tokens = tokens->next;
				i++;
			}
		}
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
