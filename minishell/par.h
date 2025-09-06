/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:59:30 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 18:28:55 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAR_H
# define PAR_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <errno.h>
# include "token.h"
# include "tree.h"
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <termios.h>

int	g_signal;

long long	ft_atoi(char *str);
size_t		ft_strlen(const char *str);
t_env		*build_env_list(char **envp);
t_env		*create_env_node(char *env_str);
void		add_env_node(t_env **head, t_env *new);
void		free_array(char **tokens);
void		free_tree(t_tree *node);
void		free_token_list(t_token *token);
void		cleanup_and_exit(t_env *env_list, char *cmd);
void		update_env(char *value, char *key, t_env **env_list);
void		free_env_list(t_env *env);
void		add_to_list(char *command, t_env **env_list);
void		handle_sigint(int sig);
void		setup_signals(void);
void		ft_putstr_fd(char *s, int fd);
void		*ft_memset(void *buffer, int c, size_t len);
void		print_error_exec(char *str, char *cmd);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strchr(char *str, int ch);
char		*ft_strndup(char *s1, char c);
char		**ft_split(char *s, char c);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*get_env_value(t_env *env, char *key);
char		*expand_cmd(char *cmd, t_env *env);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
char		**ft_token(char *cmd, t_env *env);
char		*strip_quotes(char *str);
char		*get_path(char *cmd, t_env **env);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*join_and_free(char *s1, char *s2);
char		*get_key(char *input, int start, int key_len);
char		*get_key_value(char *key, t_env *env, int exit_status);
char		**env_list_to_array(t_env *env);
char		*search_in_paths(char **paths, char *cmd, char *cwd);
char		*check_direct_path(char *cmd);
char		*handle_variable_expansion(char *input, int *i, t_env *env,
				char *result);
int			ft_strcmp(char *s1, char *s2);
int			is_all_whitespace(char *str);
int			ft_isspace(char c);
int			pars(char **cmd, t_env *env);
int			exit_hadi(char **command);
int			echo_function(char **command);
int			check_flags(char *str);
int			print_pwd(void);
int			get_the_env(char **command, t_env *env_list);
int			handle_export(char **command, t_env	**env_list);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			variable_exists(char *command, t_env *env_list);
int			handle_unset(char **command, t_env **env);
int			check_args(char *command);
int			check_equal(char *command);
int			print_export_list(t_env *env);
int			handle_cd(char **command, t_env **env_list);
int			is_builtin(char *cmd);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			execute_tree(t_tree *tree, t_env *env_list);
int			execute_builtin(t_tree *t_tree, t_env **env_list);
int			execute_pipe(t_tree *tree, t_env **env_list);
int			count_env(t_env *env);
int			ft_isalnum(int c);
int			get_key_len(char *input, int start);
int			pars_is_operator(char *token);
int			pars_is_redirection(char *token);
int			ft_isdigit(int c);
int			check_ambiguous(t_token *tokens);
int			read_heredoc_content(char *delimiter, int flag, t_env *env);
int			execute_command(t_tree *tree, t_env **env_list);
int			handle_redirections(t_tree *tree, t_env **env_list);
int			check_empty_command(t_tree *tree, char **envp, t_env **env_list);
int			handle_builtin(t_tree *tree, char **envp, t_env **env_list);
int			check_dot_command(t_tree *tree, char **envp, t_env **env_list);
int			right_fork_error(int fd_0, int fd_1, t_env **env_list, 
				pid_t pid_left);
int			left_fork_error(int fd_0, int fd_1, t_env **env_list);
char		*expand_cmd_heredoc(char *input, t_env *env);
char		*handle_dollar_quote(char *result, char c, int *i);
int			update_quote_state(char c, int *single_quote, int *double_quote);
char		*append_char(char *str, char c);

#endif