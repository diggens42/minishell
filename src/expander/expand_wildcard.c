/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:27:41 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/11 00:59:54 by fwahl            ###   ########.fr       */
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
			return (false);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}

//iterates over all directory entries and appends matches to result string
static char	**match_dir_entries(DIR *dir, char *pattern)
{
	char			**res;
	struct dirent	*ent;
	char			*filename;

	res = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		filename = ent->d_name;
		if (filename[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_wc(pattern, filename))
			res = ft_strarray_append(res, filename);
	}
	return (res);
}

//expands wildcard patterns by matching against files in cwd
char	**expand_wildcard(char *content)
{
	char	**res;
	char	*cwd;
	DIR		*dir;
	char	*temp;

	temp = ft_strdup(content);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL); // TODO handle error unable to get cwd
	dir = opendir(cwd);
	res = match_dir_entries(dir, content);
	closedir(dir);
	free(cwd);
	if (res == NULL)
		return (ft_strarray_append(res, temp));
	free(temp);
	return (res);
}
char	**insert_expanded_wc(char **argv, int *index, char **expanded_content)
{
	int		argc;
	int		size;
	char	**res;

	argc = ft_strarray_len(argv);
	size = ft_strarray_len(expanded_content);
	res = malloc((argc + size) * sizeof(char *));
	ft_memcpy((char *)res, (char *)argv, *index * sizeof(char *));
	ft_memcpy((char *)(res + *index), (char *)expanded_content, size * sizeof(char *));
	ft_memcpy((char *)(res + *index + size), (char *)(argv + *index + 1), size * sizeof(char *));
	free(argv[*index]);
	free(argv);
	free(expanded_content);
	*index += size;
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
		*type[n_argv] = COMMAND;
		n_argv++;
	}
	return (type);
}
