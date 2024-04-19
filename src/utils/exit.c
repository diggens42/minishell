/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:20 by mott              #+#    #+#             */
/*   Updated: 2024/04/19 18:33:05 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// close file descriptor, free memory and exit minishell
void	ft_exit(t_mini *mini, int exit_status)
{
	close_fd(mini);
	free_env_list(mini->env);
	free_ast(mini->ast);
	free(mini);
	exit(exit_status);
}

// bash: command: error message
void	ft_perror(char *command, char *error_message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// bash: command: `argument': error message
void	ft_perror_2(char *command, char *argument, char *error_message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// bash: syntax error near unexpected token `content'
void	ft_perror_3(char *content)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

// bash: unexpected EOF while looking for matching `content'
void	ft_perror_4(char content)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("unexpected EOF while looking for matching `", STDERR_FILENO);
	ft_putchar_fd(content, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
