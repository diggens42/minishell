/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/04 15:32:57 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_execute_commands(t_token *tokens)
{
	pid_t	child_pid;
	char	**path;
	char	*pathname;
	// char	**argv;
	char	*argv[] = {"ls", "-la", NULL};
	// char	**envp;

	(void)tokens;
	child_pid = fork();
	if (child_pid == -1)
		ms_exit();
	if (child_pid == 0)
	{
		if (ft_strchr(tokens->content, '/') != NULL)
			pathname = tokens->content;
		else if (ft_strchr(tokens->content, '/') == NULL)
		{
			path = ms_create_pathname(tokens);
			pathname = ms_find_pathname(path);
		}
		if (execve(pathname, argv, NULL) == -1)
		{
			perror("execve");
			ms_exit();
		}
	}
	waitpid(child_pid, NULL, 0);
}

// ls
// /bin/ls
// ../../../../../bin/ls

char	**ms_create_pathname(t_token *tokens)
{
	char	**path;
	char	*temp;
	int		i;

	temp = getenv("PATH");
	path = ft_split(temp, ':');
	i = 0;
	while (path[i] != NULL)
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		free(temp);
		temp = path[i];
		path[i] = ft_strjoin(temp, tokens->content);
		free(temp);
		i++;
	}
	return (path);
}

char	*ms_find_pathname(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}
