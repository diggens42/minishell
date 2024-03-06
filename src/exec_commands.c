/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 17:44:17 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute_commands(t_token *tokens, t_env *env)
{
	pid_t	child_pid;
	char	**path;
	char	*pathname;
	char	**argv;
	char	**envp;

	child_pid = fork();
	if (child_pid == -1)
		ms_exit();
	if (child_pid == 0)
	{
		if (ft_strchr(tokens->content, '/') != NULL)
			pathname = tokens->content;
		else
		{
			path = ms_create_pathname(tokens, env);
			pathname = ms_find_pathname(path);
		}
		argv = ms_tokens_to_char_array(tokens);
		envp = ms_env_to_char_array(env);
		if (execve(pathname, argv, envp) == -1)
		{
			perror("execve");
			ms_exit();
		}
	}
	waitpid(child_pid, NULL, 0);
}

void	ft_setup_next_command(char **argv, char **envp, int i)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		ft_error("pipe", ERR_SYSTEM);
	pid = fork();
	if (pid == -1)
		ft_error("fork", ERR_SYSTEM);
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			ft_error("dup2", ERR_SYSTEM);
		close(fd_pipe[1]);
		ft_execute_program(argv[i], envp);
	}
	close(fd_pipe[1]);
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		ft_error("dup2", ERR_SYSTEM);
	close(fd_pipe[0]);
}

char	**ms_tokens_to_char_array(t_token *tokens)
{
	char	**argv;
	int		n_tokens;
	int		i;

	n_tokens = ms_tokens_size(tokens);
	argv = malloc(sizeof(char *) * (n_tokens + 1));
	if (argv == NULL)
		ms_exit();
	i = 0;
	while (i < n_tokens)
	{
		argv[i] = tokens->content;
		tokens = tokens->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
