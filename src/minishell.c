/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/04/05 17:27:11 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_input(char *cmd_line, t_env *env)
{
	t_token	*token;
	t_ast	*ast;

	// int	exit_status;

	token = tokenizer(cmd_line); // free here?
	// check_tokens(token);
	// free(cmd_line);
	ast = ast_parser(&token);
	// print_ast(ast, 0);
	init_fd(env);
	env->exit_status = exec_main(ast, env);
		// fprintf(stderr, "\x1b[33mExit status: %d\n\x1b[0m", env->exit_status);
	reset_fd(env);
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
		// fprintf(stderr, "\x1b[33mHere! %s\n\x1b[0m", cmd_line);
		add_history(cmd_line);
		// fprintf(stderr, "\x1b[33mHere!\n\x1b[0m");
		if (cmd_line == NULL)
			return (EXIT_SUCCESS);
		if (cmd_line[0] == '\0')
		{
			free(cmd_line);
			continue ;
		}
		if (cmd_line[ft_strlen(cmd_line) - 1] == '\\')
			cmd_line = multi_cmd_line(cmd_line);
		handle_input(cmd_line, env);
		// free(cmd_line);
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
		exit_status = handle_input(line, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = init_env(envp);
	if (argc > 1)
		return (run_script(argv[1], env));
	// signal(SIGINT, ctrl_c_handler);
	// signal(SIGQUIT, ctrl_backslash_handler);
	// disable_signal_echo();
	return (read_eval_print_loop(env));
}
