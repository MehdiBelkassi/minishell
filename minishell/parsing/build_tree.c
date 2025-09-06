/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:08:57 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/24 15:23:34 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	copy_cmd_skip_redirs(t_token *start, t_token *end, char **cmd)
{
	t_token	*token;
	int		i;

	token = start;
	i = 0;
	while (token != end)
	{
		if (redir_type(token))
		{
			token = token->next;
			if (token)
				token = token->next;
		}
		else
		{
			cmd[i] = ft_strdup(token->value);
			i++;
			token = token->next;
		}
	}
	cmd[i] = NULL;
}

t_tree	*parse_command(t_token *start, t_token *end)
{
	int		count;
	t_token	*token;
	t_tree	*tree;
	int		quotes_flag;

	token = start;
	quotes_flag = start->quotes;
	count = 0;
	while (token != end)
	{
		if (redir_type(token))
			token = token->next->next;
		else
		{
			count++;
			token = token->next;
		}
	}
	tree = create_tree_node(N_CMD, quotes_flag);
	tree->cmd = malloc(sizeof(char *) * (count + 1));
	if (!tree->cmd)
		return (NULL);
	token = start;
	copy_cmd_skip_redirs(start, end, tree->cmd);
	return (tree);
}

t_tree	*parse_redirection(t_token *start, t_token *end, t_env *env)
{
	t_tree			*cmd;
	t_redir_data	data;

	ft_memset(&data, 0, sizeof(t_redir_data));
	cmd = parse_command(start, end);
	process_redirections(start, end, &data, env);
	return (apply_redirections(cmd, &data));
}

t_tree	*parse_tokens(t_token *start, t_token *end, t_env *env, int exit_status)
{
	t_token	*token;
	t_tree	*pipe_node;

	token = start;
	while (token && token != end)
	{
		if (token->type == T_PIPE)
		{
			pipe_node = create_tree_node(N_PIPE, token->quotes);
			if (!pipe_node)
				return (NULL);
			pipe_node->left = parse_tokens(start, token, env, exit_status);
			pipe_node->right = parse_tokens(token->next, end, env, exit_status);
			return (pipe_node);
		}
		token = token->next;
	}
	return (parse_redirection(start, end, env));
}
