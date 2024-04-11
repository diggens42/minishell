/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:52:53 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/11 23:16:15 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->value != NULL)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
