/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:39:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/19 20:59:18 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

static int	unset_cmp(char *arg, t_env **current, t_env **previous, t_env **env)
{
	if (ft_strcmp((*current)->key, arg) == 0)
	{
		if (previous == NULL)
			*env = (*current)->next;
		else
			(*previous)->next = (*current)->next;
		free_env_node((*current));
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	builtin_unset(char **argv, t_env **env)
{
	t_env	*current;
	t_env	*previous;
	int		i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (is_valid_key(argv[i], "unset") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = *env;
		previous = NULL;
		while (current != NULL)
		{
			if (unset_cmp(argv[i], &current, &previous, env) == EXIT_SUCCESS)
				break ;
			previous = current;
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}
