/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:01:13 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 13:16:37 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct s_redir_data
{
	t_token	*last_output_redir;
	t_token	*last_input_redir;
	int		heredoc_fd;
}	t_redir_data;

typedef enum s_node_type
{
	N_CMD,
	N_PIPE,
	N_RIDIR_IN,
	N_RIDIR_OUT,
	N_APPEND,
	N_HEREDOC,
}	t_node_type;

typedef struct s_tree
{
	char			**cmd;
	char			*filename;
	t_node_type		type;
	struct s_tree	*right;
	struct s_tree	*left;
	int				fd;
	int				heredoc_fd;
	int				quotes;
	int				file_quoted;
}	t_tree;

typedef struct s_env
{
	char			*value;
	char			*key;
	int				exit_status;
	struct s_env	*next;
}	t_env;

t_token	*convert_tokens(char **str_token, t_env *env);
t_tree	*create_tree_node(int type, int flag);
t_tree	*create_redir_node(t_token *redir_token, int heredoc_fd);
t_tree	*apply_redirections(t_tree *cmd, t_redir_data *data);
t_tree	*parse_tokens(t_token *start, t_token *end, t_env *env,
			int exit_status);
void	handle_input_redir(t_token *token, t_redir_data *data,
			t_env *env);
void	process_redirections(t_token *start, t_token *end,
			t_redir_data *data, t_env *env);
void	copy_cmd_skip_redirs(t_token *start, t_token *end, char **cmd);
void	handle_output_redir(t_token *token, t_redir_data *data);
int		redir_type(t_token *token);
int		get_redir_type(t_token_type type);
int		node_type(t_token *token);

#endif