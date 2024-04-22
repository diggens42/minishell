/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:32:21 by mott              #+#    #+#             */
/*   Updated: 2024/04/22 20:08:40 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_heredoc_int = 0;

static void	ctrl_c_handler_heredoc(int signal)
{
	(void)signal;
	g_heredoc_int = 1;
}

// creates a temporary file to read heredoc
static char	*open_heredoc(int *fd)
{
	static int	i;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("temp_heredoc_", num);
	free(num);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == ERROR)
		ft_perror("open", strerror(errno));
	return (filename);
}

// reads heredoc and writes to a temporary file
static void	exec_heredoc(t_mini *mini, char *limiter, int fd)
{
	char	*line;

	limiter = ft_strjoin(limiter, "\n");
	proccess_commands(mini, &limiter);
	signal(SIGINT, ctrl_c_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		ft_putstr_fd(PROMPT_MULTI_LINE, mini->fd_stdout);
		line = get_next_line(mini->fd_stdin);
		if (line == NULL || g_heredoc_int == 1 || ft_strcmp(line, limiter) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	init_parent_signals();
	get_next_line(-1);
	if (line)
		free(line);
	free(limiter);
}

// searches the AST for heredoc redirections
void	find_heredoc(t_mini *mini, t_ast *ast)
{
	int		i;
	int		fd;
	char	*filename;

	if (ast == NULL)
		return ;
	find_heredoc(mini, ast->left);
	find_heredoc(mini, ast->right);
	i = 0;
	while (ast->cmd != NULL && ast->cmd->redir[i] != NULL)
	{
		if (ast->cmd->redir[i]->type == REDIR_HEREDOC)
		{
			filename = open_heredoc(&fd);
			if (fd == ERROR)
				return ;
			exec_heredoc(mini, ast->cmd->redir[i]->file, fd);
			free(ast->cmd->redir[i]->file);
			ast->cmd->redir[i]->file = filename;
			close(fd);
		}
		i++;
	}
}
