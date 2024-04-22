/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:47:43 by mott              #+#    #+#             */
/*   Updated: 2024/03/04 15:23:26 by mott             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "include.h"

//----------------------------------------------------------------------------//
//------------------------------------------LEXER-----------------------------//
//----------------------------------------------------------------------------//
//--------------lexer_main---------//
t_token	*tokenizer(char *user_input);
int		set_token_length(char *user_input);
t_type	set_type(char *content, int token_length);
//--------------syntax-------------//
bool	quotes_syntax(char *cmd_line);
int		operator_syntax(t_token *token);
int		parenthesis_syntax(t_token *token);
//--------------utils--------------//
t_token	*new_token(void);
t_token	*token_last(t_token *token);
void	token_add_back(t_token **token, t_token *new_token);
int		tokens_size(t_token *tokens);
int		get_single_char_len(char c);
//----------------------------------------------------------------------------//
//------------------------------------------PARSER----------------------------//
//----------------------------------------------------------------------------//
//--------------expander_main------//
t_ast	*ast_parser(t_mini *mini, t_token **token);
void	ast_redirect(t_ast *cmd_node, t_token **token, int *i);
//--------------utils--------------//
t_ast	*new_ast_node(t_token *token);
void	advance_and_free_token(t_token **token);
bool	is_redirect(t_type type);
bool	is_logical(t_type type);
bool	is_operator(t_type type);
bool	is_cmd(t_type type);
bool	is_parenthesis(t_type type);
//----------------------------------------------------------------------------//
//------------------------------------------EXPANDER--------------------------//
//----------------------------------------------------------------------------//
//--------------expander_main------//
void	expand(t_mini *mini, t_cmd **cmd);
//--------------cmd----------------//
char	*expand_str_with_quotes(t_mini *mini, char *str);
void	proccess_commands(t_mini *mini, char **content);
//--------------special_params-----//
char	*expand_dollar_skip_quoted(t_mini *mini, const char *content);
char	*expand_dollar_sign(t_mini *mini, const char *content);
char	*expand_dollar_qmark(t_mini *mini, char *content);
char	*expand_exit_status(t_mini *mini, char *result);
//--------------glob---------------//
char	**expand_wildcard(char *content);
char	**insert_wildcard(char **argv, int *index, char **expanded_content);
t_type	**set_type_wildcard(char **argv, int index);
//--------------quotes-------------//
char	*expand_double_quote(t_mini *mini, const char *content);
char	*remove_quotes(const char *content);
char	*get_quote_start(char *str);
char	*get_quote_end(char *str, char quote_type);
int		set_quote_state(int quote_state, char c);
//----------------------------------------------------------------------------//
//------------------------------------------EXECUTOR--------------------------//
//----------------------------------------------------------------------------//
//--------------exec_main----------//
int		exec_main(t_mini *mini, t_ast *ast);
int		exec_builtin(t_mini *mini, char **argv);
void	exec_finish(t_mini *mini, char **argv);
//--------------heredoc------------//
void	find_heredoc(t_mini *mini, t_ast *ast);
//--------------path---------------//
char	*create_absolute_path(t_mini *mini, char *command);
char	*create_relative_path(t_mini *mini, char *command);
//--------------pipe---------------//
int		exec_pipe(t_mini *mini, t_ast *ast, int lvl);
//--------------redir--------------//
int		exec_set_redir(t_mini *mini, t_redir **redir);
//--------------utils_1------------//
int		ft_pipe(int *fd);
pid_t	ft_fork(void);
int		set_fd(t_mini *mini);
int		reset_fd(t_mini *mini);
int		close_fd(t_mini *mini);
//--------------utils_2------------//
char	**env_to_char_array(t_env *env);
int		envp_size(t_env *env);
char	*ft_tolower_str(char *str);
char	**new_argv(char **old_argv);
int		waitpid_exit_stat(pid_t pid);
//----------------------------------------------------------------------------//
//-----------------------------------------BUILTINS---------------------------//
//----------------------------------------------------------------------------//
int		builtin_cd(char **argv, t_env **env);
int		builtin_echo(char **argv);
int		builtin_env(t_env *env);
int		builtin_exit(char **argv, t_mini *mini);
int		builtin_export(char **argv, t_env **env);
int		builtin_pwd(void);
int		builtin_unset(char **argv, t_env **env);
//--------------utils--------------//
int		env_update(t_env **env, char *key, char *value);
int		is_valid_key(char *key, char *builtin);
int		builtin_export_print(t_env *env);
//----------------------------------------------------------------------------//
//-----------------------------------------UTILS------------------------------//
//----------------------------------------------------------------------------//
//--------------env----------------//
t_env	*init_env(char **envp);
char	*ft_getenv(char *key, t_env *env);
void	append_env_node(t_env **head, t_env *new_node);
t_env	*new_env_node(char *key, char *value);
//--------------exit---------------//
void	ft_exit(t_mini *mini, int exit_status);
void	ft_perror(char *command, char *error_message);
void	ft_perror_2(char *command, char *argument, char *error_message);
void	ft_perror_3(char *content);
void	ft_perror_4(char content);
//--------------free---------------//
void	free_token_list(t_token *token_head);
void	free_env_list(t_env *env);
void	free_type_array(t_type **type);
void	free_ast(t_ast *ast);
//--------------signal-s-----------//
void	init_parent_signals(void);
void	init_child_signals(void);
void	init_readline_signal_flags(void);

#endif
