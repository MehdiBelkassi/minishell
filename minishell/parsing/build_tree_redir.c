/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:53:11 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/24 13:43:10 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	handle_output_redir(t_token *token, t_redir_data *data)
{
	int	fd;

	if (!token->next)
		return ;
	if (token->type == T_REDIR_OUT)
	{
		fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(fd);
	}
	else if (token->type == T_APPEND)
	{
		fd = open(token->next->value, O_WRONLY | O_CREAT, 0644);
		close(fd);
	}
	data->last_output_redir = token;
}

void	handle_input_redir(t_token *token, t_redir_data *data,
	t_env *env)
{
	if (!token->next)
		return ;
	if (token->type == T_REDIR_IN)
		data->last_input_redir = token;
	else if (token->type == T_HEREDOC)
	{
		data->heredoc_fd = read_heredoc_content(ft_strdup(token->next->value),
				token->next->quotes, env);
		data->last_input_redir = token;
	}
}

void	process_redirections(t_token *start, t_token *end,
	t_redir_data *data, t_env *env)
{
	t_token	*token;

	token = start;
	while (token && token != end)
	{
		if (redir_type(token) == 1)
		{
			if (token->type == T_REDIR_OUT || token->type == T_APPEND)
				handle_output_redir(token, data);
			else if (token->type == T_REDIR_IN || token->type == T_HEREDOC)
				handle_input_redir(token, data, env);
			if (token->next)
				token = token->next;
		}
		token = token->next;
	}
}

t_tree	*create_redir_node(t_token *redir_token, int heredoc_fd)
{
	t_tree	*redir;

	redir = create_tree_node(get_redir_type(redir_token->type),
			redir_token->quotes);
	if (!redir)
		return (NULL);
	if (redir_token->type == T_HEREDOC)
		redir->fd = heredoc_fd;
	else
	{
		redir->filename = ft_strdup(redir_token->next->value);
		redir->file_quoted = redir_token->next->quotes;
	}
	return (redir);
}

t_tree	*apply_redirections(t_tree *cmd, t_redir_data *data)
{
	t_tree	*redir;

	if (data->last_output_redir)
	{
		redir = create_redir_node(data->last_output_redir, 0);
		if (!redir)
			return (NULL);
		redir->left = cmd;
		cmd = redir;
	}
	if (data->last_input_redir)
	{
		redir = create_redir_node(data->last_input_redir, data->heredoc_fd);
		if (!redir)
			return (NULL);
		redir->left = cmd;
		cmd = redir;
	}
	return (cmd);
}
