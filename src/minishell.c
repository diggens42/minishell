/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/22 18:11:10 by fwahl            ###   ########.fr       */
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
	// char		*limiter;
	t_token		*token_head;
	t_ast		*ast_head;
	t_exec		*exec;

	while (true)
	{
		exec = init_fd();
		user_input = readline(PROMPT_STD);
		add_history(user_input);
		if (user_input == NULL)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue ;
		}
		// else if (ft_strstr(user_input, "<<") != NULL)
		// {
		// 	limiter = find_limiter(ft_strstr(user_input, "<<"));
		// 	while (true)
		// 	{
		// 		user_input2 = readline(PROMPT_MULTI_LINE);
		// 		if (ft_strncmp(user_input2, limiter, ft_strlen(limiter)) == 0)
		// 		{
		// 			free(user_input2);
		// 			free(limiter);
		// 			break ;
		// 		}
		// 		temp = user_input;
		// 		user_input = ft_strjoin(user_input, user_input2);
		// 		free (temp);
		// 		free (user_input2);
		// 	}
		// }
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
		exec_main(ast_head, env, exec);
		reset_fd(exec);
	}
}

char	*find_limiter(char *user_input)
{
	char	*limiter;
	int		i;

	while (*user_input == '<' || ft_isspace(*user_input) == true)
		user_input++;
	i = 0;
	while (user_input[i] != '\0' && ft_isspace(user_input[i]) == false)
		i++;
	if (i == 0)
		return (NULL);
	limiter = ft_substr(user_input, 0, i);
	if (limiter == NULL)
		ft_exit(NULL);
	return (limiter);
}
