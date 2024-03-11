/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:54:37 by mott              #+#    #+#             */
/*   Updated: 2024/03/11 17:52:06 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
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
	t_ast_node	*ast_head;

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
			temp = user_input;
			user_input = ft_strjoin(user_input, user_input2);
			free (temp);
			free (user_input2);
		}
		token_head = tokenizer(user_input, env);
		free(user_input);

		ast_head = build_ast_simple(token_head);
		free_token_list(token_head);

		init_executor(ast_head, env);
		free_char_array(ast_head->argv);
		free(ast_head);
	}
}
