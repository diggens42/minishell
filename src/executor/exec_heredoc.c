/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:32:21 by mott              #+#    #+#             */
/*   Updated: 2024/04/10 17:02:29 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_heredoc(t_ast *ast)
{
	int	i;
	int	heredoc;

	i = 0;
	heredoc = 0;
	while (ast->cmd->redir[i] != NULL)
	{
		if (ast->cmd->redir[i]->type == REDIR_HEREDOC)
			heredoc++;
		i++;
	}
	return (heredoc);
}

int	exec_here_doc(char *limiter, t_env *env)
{
	// fprintf(stderr, "\x1b[33mexec_here_doc: %s\n\x1b[0m", limiter);

	int		fd[2];
	char	*line;

	limiter = ft_strjoin_free(limiter, "\n");
	ft_pipe(fd);
	while (true)
	{
		ft_putstr_fd(PROMPT_MULTI_LINE, env->fd_stdout);
		line = get_next_line(env->fd_stdin);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
