/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/01 20:54:23 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*ms_cd_rel_path(t_token *tokens)
// {
// 	char	*cwd;
// 	char	*temp_path;
// 	char	*rel_path;
// 	size_t	rel_path_len;

// 	cwd = getcwd(NULL, 0);
// 	if (cwd == NULL)
// 		return ; //TODO errorhandling
// 	temp_path = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
// 	temp_path = ft_strjoin(cwd, "/");
// 	rel_path_len = ft_strlen(temp_path) + ft_strlen(tokens->token) + 1; // +1 for nullterm, +1 for added /
// 	rel_path = malloc(sizeof(char) * rel_path_len);
// 	rel_path = ft_strjoin(temp_path, tokens->token);
// 	free(temp_path);
// 	free(cwd);
// 	return (rel_path);
// }

// TODO
// '~' ???
void	ms_cd(t_token *tokens)
{
	char	*path;

	// if (tokens == NULL)
	// 	return ; //TODO errorhandling
	if (tokens->next == NULL)
		path = getenv("HOME");
	else
		path = tokens->next->content;
	if (chdir(path) == -1)
	// {
		perror("chdir");
		// return ; //TODO errorhandling
	// }
}

	// if (tokens->token[0] != '/')
	// 	path = ms_cd_rel_path(tokens);
