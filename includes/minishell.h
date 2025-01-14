/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:34:55 by cvarela-          #+#    #+#             */
/*   Updated: 2024/07/03 16:49:49 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

extern long long	g_exit_status;

//PARSER/TOKEN/DEF_TOKEN_TYPE.C
int				is_option(char *str);
int				is_pipe(char *str);
int				is_redirect(char *str, int was_quoted);

//UTILS/UTILS.C
int				isquote(int c);
int				has_empty_pipe(char **splitted);
int				lstsize_tokens(t_tokens *token, int filter);
int				search_ops_in_str(char *s1, char *s2);
void			change_flag(bool *flag);

//UTILS/UTILS2.C
char			**fill_ops(void);
char			**fill_args(t_tokens *token);
char			**fill_env_matrix(t_env *env);
int				is_accepted(t_tokens *token);
int				is_bin(char *str);
int				is_digit_signal(char *str);

//PARSER/CREATE_COMMANDS_LIST.C
void			pipe_commands(char *str, t_env *env, t_commands *head);
int				lstsize_commands(t_commands *commands);
void			lstadd_back_commands(t_commands **lst, t_commands *new);
t_commands		*lstlast_commands(t_commands *lst);

//PARSER/CREATE_COMMANDS_LIST_UTILS.C
void			remake_commands(t_commands *commands);

//PARSER/CREATE_COMMANDS_LIST_UTILS2.C
t_commands		*create_command_list(char *str, t_env *env);
char			**split_commands(char *str);
void			free_pipe_splitted(char **pipe_splitted);
void			add_nodes_to_command_list(t_commands **head,
					char **pipe_splitted, t_env *env);

//PARSER/PARSER.C
int				process_tokens(t_commands *command);
void			parser(t_commands *command);
char			*process_argument(t_commands *command);

//PARSER/PARSER_UTILS.C
int				search_content(char *str, char *op, int flag);
void			handle_content_before(t_tokens *token, int pos,
					char *op_str, char *original_str);
t_tokens		*handle_content_after(char *original_str, int pos,
					char *op, t_tokens *token);
char			*quote_handler(char *str, int *pos, int start, t_env *env);
char			*process_variable(char *str, int *i,
					char *expanding, t_env *env);

//PARSER/PARSER_UTILS2.C
char			*get_variable(char *str, int *pos);
char			*search_variable(char *command, int *pos, t_env *env);
char			*add_chars(char *expanding_str, char *str, int pos, int start);
char			*if_variable(char *new_str, t_commands *command,
					int *start, int *i);
char			*if_quotes(char *new_str, t_commands *command,
					int *start, int *i);

//PARSER/PARSER_UTILS3.C
int				check_redir(t_commands *commands);
int				has_in_out(t_commands *command, t_tokens *head);
void			search_for_redirs(t_commands *command);
int				function(t_commands *command);

//PARSE/PARSER_UTILS4.C
int				has_open_quotes(const char *str, int len);

//PARSER/TOKEN/CREATE_TOKEN_LIST.C
t_tokens		*token_list(char *line);
t_tokens		*lstnew_token(char *str, t_TokenType type);
t_TokenType		token_type(char *str, int flag, int was_quoted);
void			lstadd_back_token(t_tokens **lst, t_tokens *new);

//PARSER/TOKEN/TOKEN_UTILS.C
t_TokenType		which_red(char *str);

//BUILTINS/CHECK_BUILTINS.C
int				check_builtins(t_commands *command);
int				check(t_commands *command);

//BINS/CHECK_BINS.C
int				check_bins(t_tokens *token, t_env *env);
int				run_cmd(char *bin_path, t_tokens *token, t_env *env, int flag);
int				env_len(t_env *env);

//BINS/CHECK_BINS_UTILS.C
char			**get_path(t_env *env);
char			*get_bin_path(char *path, char *str);
void			check_heredoc(t_tokens *token);
void			execute_cicle(char *delim_line);

//BINS/SIGNAL_HANDLER.C
void			handle_global_signals(void);
void			handle_cmd_signals(void);

//BINS/SIGNAL_HANDLER2.C
void			handle_signal_redir(void);
//BUILTINS/ECHO/ECHO.C
int				print(t_tokens *token);

//BUILTINS/DIRECTORY/DIRECTORY.C
int				change_dir(t_tokens *token, t_env *env);

//BUILTINS/EXPORT/EXPORT.C
void			export(t_commands *command);
char			*form_variable(char *name, char *value);

//BUILTINS/ENV/ENV.C
int				env(t_env *env, int flag);
char			*env_value(char *str, t_env *env);

//BUILTINS/ENV/UNSET.C
int				unset(t_tokens *token, t_env *env);

//PARSER/ENV/CREATE_ENV_LIST.C
t_env			*init_env(char **envp);
t_env			*lstnew_env(char *envp, int flag);
void			lstadd_back_env(t_env **lst, t_env *new);

//SRC/PIPE/PIPE.C
void			open_pipe(t_commands *commands);

//SRC/PIPE/FREE_STRUCTS.C
void			free_structs(t_commands *commands, int flag);
void			free_env(t_env *env);
void			free_structs2(t_commands *commands);

//SRC/REDIRECTIONS/REDIR.C
int				files_exist(t_tokens *token);
int				handle_redir(t_tokens *token);
void			heredoc_while(char *delim);

//SRC/BUILTINS/EXIT.C
int				exit_terminal(t_commands *command);

#endif
