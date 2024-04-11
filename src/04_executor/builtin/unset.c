/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:39:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/11 23:16:29 by fwahl            ###   ########.fr       */
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

int	builtin_unset(char **argv, t_env **env) //TODO
{
	t_env	*current;
	t_env	*previous;
	int		i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (is_valid_key(argv[i]) == EXIT_FAILURE)
		{
			ft_perror_2("unset", argv[i], "not a valid identifier");
			return (EXIT_FAILURE);
		}
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
