/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:16:40 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/01 19:04:59 by fwahl            ###   ########.fr       */
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

void	ms_cd(t_token *tokens)
{	
	char	*path;
	
	tokens = tokens->next;
	path = tokens->token;
	if (tokens == NULL)
		return ; //TODO errorhandling
	if (chdir(path) != 0)
		return ; //TODO errorhandling
}

	// if (tokens->token[0] != '/')
	// 	path = ms_cd_rel_path(tokens);