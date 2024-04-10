/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:06:45 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/10 20:40:56 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	n_wc_matches(char *expanded_content)
{
	int		argc;
	char	*temp;
	char	*token;
	char	*delim;

	argc = 1;
	temp = ft_strdup(expanded_content);
	delim = " ";
	token = ft_strtok(temp, delim);
	while (token != NULL)
	{
		argc++;
		token = ft_strtok(NULL, delim);
	}
	free(temp);
	return (argc);
}

static char	**alloc_new_argv(char **argv, int n_wc)
{
	int		i;
	int		new_argc;
	char	**new_argv;

	i = 0;
	while (argv[i] != NULL)
		i++;
	new_argc = i + n_wc + 1;
	new_argv = (char **)ft_calloc(new_argc, sizeof(char *));
	return (new_argv);
}

static void	insert_wc(char **new_argv, int index, char *expanded_content)
{
	int		j;
	char	*temp;
	char	*token;

	j = index;
	temp = ft_strdup(expanded_content);
	token = ft_strtok(temp, " ");
	while (token != NULL)
	{
		new_argv[j++] = ft_strdup(token);
		token = ft_strtok(NULL, " ");
	}
	free(temp);
}

static void	copy_after_index(char **argv, char **new_argv, int index)
{
	int	i;
	int	j;

	i = index + 1;
	j = 0;
	while (new_argv[j] != NULL)
		j++;
	while (argv[i] != NULL)
	{
		new_argv[j] = ft_strdup(argv[i]);
		j++;
		i++;
	}
}

char	**insert_expanded_wc(char **argv, int index, char *expanded_content)
{
	int		n_wc;
	int		i;
	char	**new_argv;

	n_wc = n_wc_matches(expanded_content);
	new_argv = alloc_new_argv(argv, n_wc);
	i = 0;
	while (i < index)
	{
		new_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	insert_wc(new_argv, index, expanded_content);
	copy_after_index(argv, new_argv, index);
	return (new_argv);
}
