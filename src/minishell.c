/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/04/17 21:46:04 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_input(t_mini *mini, char *cmd_line)
{
	int		exit_status;

	if (quotes_syntax(cmd_line) == true)
		return (2);
	mini->token = tokenizer(cmd_line);
	exit_status = operator_syntax(mini->token);
	if (exit_status != EXIT_SUCCESS)
	{
		free_token_list(mini->token);
		mini->exit_status = exit_status;
		return (exit_status);
	}
	exit_status = parenthesis_syntax(mini->token);
	if (exit_status != EXIT_SUCCESS)
	{
		free_token_list(mini->token);
		mini->exit_status = exit_status;
		return (exit_status);
	}
	// check_tokens(mini->token);
	mini->ast = ast_parser(mini, &mini->token);
	// print_ast(mini->ast, 0);
	set_fd(mini);
	mini->exit_status = exec_main(mini, mini->ast);
	close_fd(mini);
	free_ast(mini->ast);
	return (mini->exit_status);
}

static char	*multi_cmd_line(char *cmd_line)
{
	char		*next_cmd_line;
	char		*temp;

	while (cmd_line[ft_strlen(cmd_line) - 1] == '\\')
	{
		cmd_line[ft_strlen(cmd_line) - 1] = '\0';
		next_cmd_line = readline(PROMPT_MULTI_LINE);
		temp = cmd_line;
		cmd_line = ft_strjoin(cmd_line, next_cmd_line);
		free(temp);
		free(next_cmd_line);
	}
	return (cmd_line);
}

static int	read_eval_print_loop(t_mini *mini)
{
	char	*cmd_line;

	while (true)
	{
		cmd_line = readline(PROMPT_STD);
		add_history(cmd_line);
		if (cmd_line == NULL)
		{
			free_env_list(mini->env);
			free(mini);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
		if (cmd_line[0] == '\0'
			|| (cmd_line == NULL && ft_strlen(cmd_line) == 0))
		{
			free(cmd_line);
			continue ;
		}
		if (cmd_line[ft_strlen(cmd_line) - 1] == '\\')
			cmd_line = multi_cmd_line(cmd_line);
		mini->exit_status = handle_input(mini, cmd_line);
		free(cmd_line);
	}
}

// static int	run_script(t_mini *mini, char *filename)
// {
// 	int		fd;
// 	char	*line;
// 	int		exit_status;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (127);
// 	exit_status = EXIT_SUCCESS;
// 	while (true)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			return (exit_status);
// 		if (*line == '#')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		mini->exit_status = handle_input(mini, line);
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	mini->env = init_env(envp);
	// if (argc > 1)
	// 	return (run_script(mini, argv[1]));
	init_parent_signals();
	init_readline_signal_flags();
	return (read_eval_print_loop(mini));
}
