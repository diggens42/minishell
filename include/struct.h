/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:41:19 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/12 00:44:59 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_type
{
	UNKNOWN,
	COMMAND,
	SINGLE_QUOTE,
	DOLLAR,
	DQMARK,
	WILDCARD,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND,
	PIPE,
	AND,
	OR,
	PARENTHESIS_L,
	PARENTHESIS_R
}	t_type;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				fd_stdin; //TODO
	int				fd_stdout; //TODO
	int				exit_status; //TODO
}	t_env;

typedef struct	s_token
{
	t_type			type;
	char			*content;
	int				length;
	struct s_token	*next;
}	t_token;

typedef struct	s_redir
{
	t_type			type;
	char			*file;
}	t_redir;

typedef struct	s_cmd
{
	char			**argv;
	t_type			**type;
	t_redir			**redir;
}	t_cmd;

typedef struct	s_ast
{
	t_type			type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	bool			subshell;
}	t_ast;

// typedef struct	s_mini
// {
// 	t_ast	*ast;
// 	t_env	*env;
// 	int		fd_stdin;
// 	int		fd_stdout;
// }	t_mini;

#endif
