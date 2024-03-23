/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mott <mott@student.42heilbronn.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:39:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/23 14:59:19 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_env_node(t_env *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

int	builtin_unset(char **argv, t_env **env)
{
	t_env	*current;
	t_env	*previous;
	int		i;

	i = 0;
	while (argv[++i] != NULL)
	{
		current = *env;
		previous = NULL;
		while (current != NULL)
		{
			if (ft_strcmp(current->key, argv[i]) == 0)
			{
				if (previous == NULL)
					*env = current->next;
				else
					previous->next = current->next;
				free_env_node(current);
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}
