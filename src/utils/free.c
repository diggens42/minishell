/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:29:19 by mott              #+#    #+#             */
/*   Updated: 2024/04/18 17:52:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token_list(t_token *token_head)
{
	t_token	*temp;

	while (token_head != NULL)
	{
		temp = token_head->next;
		free(token_head->content);
		free(token_head);
		token_head = temp;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	free_type_array(t_type **type)
{
	int	i;

	i = 0;
	while (type[i] != NULL)
	{
		free(type[i]);
		i++;
	}
	free(type);
}

void	free_redir_array(t_redir **redir)
{
	int	i;

	i = 0;
	while (redir[i] != NULL)
	{
		free(redir[i]->file);
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->cmd != NULL)
	{
		if (ast->cmd->argv != NULL)
			ft_free_strarray(ast->cmd->argv);
		if (ast->cmd->type != NULL)
			free_type_array(ast->cmd->type);
		if (ast->cmd->redir != NULL)
			free_redir_array(ast->cmd->redir);
		free(ast->cmd);
	}
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}
