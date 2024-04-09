/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:29:19 by mott              #+#    #+#             */
/*   Updated: 2024/04/09 16:49:27 by fwahl            ###   ########.fr       */
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

void	free_char_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
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

void	free_ast(t_ast *ast)
{
	int	i;

	if (ast == NULL)
		return ;
	if (ast->cmd != NULL)
	{
		if (ast->cmd->argv != NULL)
		{
			i = 0;
			while (ast->cmd->argv[i] != NULL)
			{
				free(ast->cmd->argv[i]);
				i++;
			}
			free(ast->cmd->argv);
		}
		if (ast->cmd->type != NULL)
		{
			i = 0;
			while (ast->cmd->type[i] != NULL)
			{
				free(ast->cmd->type[i]);
				i++;
			}
			free(ast->cmd->type);
		}
		if (ast->cmd->redir != NULL)
		{
			i = 0;
			while (ast->cmd->redir[i] != NULL)
			{
				free(ast->cmd->redir[i]->file);
				free(ast->cmd->redir[i]);
			}
			free(ast->cmd->redir);
		}
		free(ast->cmd);
	}
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}
