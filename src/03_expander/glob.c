/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:27:41 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/20 16:44:03 by mott             ###   ########.fr       */
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

	while (true)
	{
		ent = readdir(dir);
		if (ent == NULL)
			break ;
		filename = ent->d_name;
		if (filename[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_wc(pattern, filename))
			res = ft_strarray_append(res, filename);
	}
	return (res);
}

// //iterates over all directory entries and appends matches to result string
// static char	**match_dir_entries(DIR *dir, char *pattern)
// {
// 	char			**res;
// 	struct dirent	*ent;
// 	char			*filename;

// 	res = NULL;
// 	while ((ent = readdir(dir)) != NULL)
// 	{
// 		filename = ent->d_name;
// 		if (filename[0] == '.' && pattern[0] != '.')
// 			continue ;
// 		if (match_wc(pattern, filename))
// 			res = ft_strarray_append(res, filename);
// 	}
// 	return (res);
// }

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
		return (NULL);
	dir = opendir(cwd);
	res = match_dir_entries(dir, content);
	closedir(dir);
	free(cwd);
	if (res == NULL)
		return (ft_strarray_append(res, temp));
	free(temp);
	return (res);
}

char	**insert_wildcard(char **argv, int *index, char **expanded_content)
{
	int		argc;
	int		n;
	char	**res;

	argc = ft_strarray_len(argv);
	n = ft_strarray_len(expanded_content);
	res = malloc((argc + n) * sizeof(char *));
	ft_memcpy((char *)res, (char *)argv, *index * sizeof(char *));
	ft_memcpy(
		(char *)(res + *index),
		(char *)expanded_content,
		n * sizeof(char *));
	ft_memcpy(
		(char *)(res + *index + n),
		(char *)(argv + *index + 1),
		(argc - *index - 1) * sizeof(char *));
	free(argv[*index]);
	free(argv);
	free(expanded_content);
	res[argc + n - 1] = NULL;
	*index += n;
	return (res);
}

t_type	**set_type_wildcard(char **argv, int index)
{
	t_type	**type;
	int		argc;
	int		len;

	len = 0;
	argc = ft_strarray_len(argv);
	type = (t_type **)ft_calloc(argc + 1, sizeof(t_type *));
	argc = 0;
	while (argc < index)
	{
		type[argc] = (t_type *)ft_calloc(1, sizeof(t_type));
		len = ft_strlen(argv[argc]);
		*type[argc] = COMMAND;
		argc++;
	}
	while (argv[argc] != NULL)
	{
		type[argc] = (t_type *)ft_calloc(1, sizeof(t_type));
		len = ft_strlen(argv[argc]);
		*type[argc] = set_type(argv[argc], len);
		argc++;
	}
	return (type);
}
