/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:31:33 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/23 17:22:31 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

t_tree	*create_tree_node(int type, int flag)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->quotes = flag;
	node->type = type;
	node->cmd = NULL;
	node->filename = NULL;
	node->fd = -1;
	node->left = NULL;
	node->right = NULL;
	node->file_quoted = 0;
	return (node);
}

int	get_redir_type(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (N_RIDIR_IN);
	else if (type == T_REDIR_OUT)
		return (N_RIDIR_OUT);
	else if (type == T_APPEND)
		return (N_APPEND);
	else
		return (N_HEREDOC);
}

int	redir_type(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_APPEND || token->type == T_HEREDOC)
		return (1);
	return (0);
}

int	node_type(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_APPEND || token->type == T_HEREDOC
		|| token->type == T_PIPE)
		return (1);
	return (0);
}
