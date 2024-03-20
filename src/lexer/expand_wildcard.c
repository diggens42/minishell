/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:27:41 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/20 19:36:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*conc_paths(char *dir_path, char *filename)
{
	size_t	dir_len;
	size_t	file_len;
	size_t	full_path_len;
	char	*full_path;

	dir_len = ft_strlen(dir_path);
	file_len = ft_strlen(filename);
	full_path_len = dir_len + file_len + 2;
	full_path = (char *)ft_calloc(1, full_path_len);
	if (full_path == NULL)
		return (NULL); //TODO handle malloc error
	ft_strlcpy(full_path, dir_path, dir_len + 1);
	full_path[dir_len] = '/';
	ft_strlcpy(full_path + dir_len + 1, filename, file_len + 1);
	return (full_path);
}

static char	*append_res(char *res, char *str)
{
	size_t	res_len;
	size_t	str_len;
	char	*new_res;

	res_len = 0;
	if (res != NULL)
		res_len = ft_strlen(res);
	str_len = ft_strlen(str);
	new_res = (char *)ft_calloc(1, res_len + str_len + 2);
	if (new_res == NULL)
	{
		free(res);
		return (NULL);
	}
	if (res_len > 0)
	{
		ft_strlcpy(new_res, res, res_len + 1);
		new_res[res_len] = ' ';
		res_len++;
	}
	ft_strlcpy(new_res + res_len, str, str_len + 1);
	if (res)
		free(res);
	return (new_res);
}

static char	*loop_dir(char *cwd, struct dirent *ent, char *pattern, char *res)
{
	char	*filename;
	char	*path;
	bool	match;

	filename = ent->d_name;
	match = match_wildcard(pattern, filename);
	if (match == true)
	{
		path = conc_paths(cwd, filename);
		res = append_res(res, path);
		free(path);
	}
	return (res);
}

static char	*match_dir_entries(DIR *dir, char *pattern, char *cwd)
{
	char			*res;
	struct dirent	*ent;

	res = NULL;
	while ((ent = readdir(dir)) != NULL)
		res = loop_dir(cwd, ent, pattern, res);
	return (res);
}

char	*expand_wildcard(char *content)
{
	char	*res;
	char	*cwd;
	DIR		*dir;

	res = NULL;
	cwd = getcwd(NULL, 0);
	if(cwd == NULL)
		return (NULL); // TODO handle error unable to get cwd
	dir = opendir(cwd);
	if (dir == NULL)
	{
		free(cwd);
		return (NULL); //TODO handle error unable to open cwd
	}
	res = match_dir_entries(dir, content, cwd);
	closedir(dir);
	free(cwd);
	return (res);
}
