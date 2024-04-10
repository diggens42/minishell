/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:27:41 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 20:39:50 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//checks if a given string matches a wildcard pattern
static int	match_wc(char *pattern, char *str)
{
	while (*pattern != '\0' && *str != '\0')
	{
		if (*pattern == '*')
			return (match_wc(pattern + 1, str) || match_wc(pattern, str + 1));
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}

//appends all wildcard matches paths into one string separated by a space
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

//iterates over all directory entries and appends matches to result string
static char	*match_dir_entries(DIR *dir, char *pattern)
{
	char			*res;
	struct dirent	*ent;
	char			*filename;

	res = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		filename = ent->d_name;
		if (filename[0] == '.')
			continue ;
		if (match_wc(pattern, filename))
			res = append_res(res, filename);
	}
	return (res);
}

//expands wildcard patterns by matching against files in cwd
char	*expand_wildcard(char *content)
{
	char	*res;
	char	*cwd;
	DIR		*dir;
	char	*temp;

	temp = ft_strdup(content);
	res = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL); // TODO handle error unable to get cwd
	dir = opendir(cwd);
	res = match_dir_entries(dir, content);
	closedir(dir);
	free(cwd);
	if (res == NULL)
	{
		free(res);
		return (temp);
	}
	free(temp);
	return (res);
}

t_type	**wc_set_type(char **argv)
{
	t_type	**type;
	int		n_argv;
	int		len;

	len = 0;
	n_argv = 0;
	while (argv[n_argv] != NULL)
		n_argv++;
	type = (t_type **)ft_calloc(n_argv + 1, sizeof(t_type *));
	n_argv = 0;
	while (argv[n_argv] != NULL)
	{
		type[n_argv] = (t_type *)ft_calloc(1, sizeof(t_type));
		len = ft_strlen(argv[n_argv]);
		*type[n_argv] = set_type(argv[n_argv], len);
		n_argv++;
	}
	return (type);
}
