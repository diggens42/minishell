/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/04/22 19:59:50 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_input(t_mini *mini, char *cmd_line)
{
	int	exit_status;

	if (quotes_syntax(cmd_line) == true)
		return (SYNTAX_ERROR);
	mini->token = tokenizer(cmd_line);
	exit_status = operator_syntax(mini->token);
	if (exit_status != EXIT_SUCCESS)
	{
		free_token_list(mini->token);
		mini->exit_status = exit_status;
		return (exit_status);
	}
	if (parenthesis_syntax(mini->token) == SYNTAX_ERROR)
	{
		free_token_list(mini->token);
		mini->exit_status = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	mini->ast = ast_parser(mini, &mini->token);
	set_fd(mini);
	find_heredoc(mini, mini->ast);
	mini->exit_status = exec_main(mini, mini->ast);
	close_fd(mini);
	free_ast(mini->ast);
	return (mini->exit_status);
}

static char	*multi_cmd_line(char *cmd_line)
{
	char	*next_cmd_line;
	char	*temp;

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

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	mini->env = init_env(envp);
	init_parent_signals();
	init_readline_signal_flags();
	return (read_eval_print_loop(mini));
}
