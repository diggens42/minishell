/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:54:02 by mott              #+#    #+#             */
/*   Updated: 2024/03/06 13:24:19 by mott             ###   ########.fr       */
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

char	**ms_create_pathname(t_token *tokens, t_env *env)
{
	char	**path;
	char	*temp;
	int		i;

	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			temp = env->value;
		env = env->next;
	}
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
