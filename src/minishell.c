/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/23 16:02:58 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	// signal(SIGINT, ctrl_c_handler);
	// signal(SIGQUIT, ctrl_backslash_handler);
	// disable_signal_echo();
	env = init_env(envp);
	read_eval_print_loop(env);
	return (EXIT_SUCCESS);
}

void	read_eval_print_loop(t_env *env)
{
	char		*user_input;
	char		*user_input2;
	char		*temp;
	t_token		*token_head;
	t_ast		*ast_head;
	t_exec		*exec;

	exec = init_fd();
	while (true)
	{
		user_input = readline(PROMPT_STD);
		add_history(user_input);
		if (user_input == NULL)
		{
			// ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue ;
		}
		while (user_input[ft_strlen(user_input) - 1] == '\\')
		{
			user_input[ft_strlen(user_input) - 1] = '\0';
			user_input2 = readline(PROMPT_MULTI_LINE);
			temp = user_input;
			user_input = ft_strjoin(user_input, user_input2);
			free(temp);
			free(user_input2);
		}
		token_head = tokenizer(user_input, env, exec);
		free(user_input);
		// check_tokens(token_head);
		ast_head = ast_parser(&token_head);
		free_token_list(token_head);
		// print_ast(ast_head, 0);
		exec->exit_status = exec_main(ast_head, env, exec);
		// fprintf(stderr, "\x1b[33mExit status: %d\n\x1b[0m", exec->exit_status);
		reset_fd(exec);
	}
}
