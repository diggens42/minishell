/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/04/10 22:23:34 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_input(char *cmd_line, t_env *env)
{
	t_token	*token;
	t_ast	*ast;
	int		exit_status;

	if (quotes_syntax(cmd_line) == true)
		return (2);
	token = tokenizer(cmd_line); // free here?
	exit_status = operator_syntax(token);
	if (exit_status != EXIT_SUCCESS)
	{
		free_token_list(token);
		env->exit_status = exit_status;
		return (exit_status);
	}
	exit_status = parenthesis_syntax(token);
	if (exit_status != EXIT_SUCCESS)
	{
		free_token_list(token);
		env->exit_status = exit_status;
		return (exit_status);
	}
	// check_tokens(token);
	ast = ast_parser(&token);
	// print_ast(ast, 0);
	set_fd(env);
	env->exit_status = exec_main(ast, env);
	close_fd(env);
	free_ast(ast);
	return (env->exit_status);
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

static int	read_eval_print_loop(t_env *env)
{
	char	*cmd_line;

	while (true)
	{
		cmd_line = readline(PROMPT_STD);
		add_history(cmd_line);
		if (cmd_line == NULL)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
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
		env->exit_status = handle_input(cmd_line, env);
		free(cmd_line);
	}
}

static int	run_script(char *filename, t_env *env)
{
	int		fd;
	char	*line;
	int		exit_status;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (127);
	exit_status = EXIT_SUCCESS;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (exit_status);
		if (*line == '#')
		{
			free(line);
			continue ;
		}
		env->exit_status = handle_input(line, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = init_env(envp);
	if (argc > 1)
		return (run_script(argv[1], env));
	init_signals();
	return (read_eval_print_loop(env));
}
