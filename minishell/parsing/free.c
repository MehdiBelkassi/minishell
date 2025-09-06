/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:19:33 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/23 22:16:24 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	free_array(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

void	free_tree(t_tree *tree)
{
	int	i;

	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	if (tree->cmd)
	{
		i = 0;
		while (tree->cmd[i])
		{
			free(tree->cmd[i]);
			i++;
		}
		free(tree->cmd);
	}
	if (tree->filename)
		free(tree->filename);
	free(tree);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	cleanup_and_exit(t_env *env_list, char *cmd)
{
	free(cmd);
	free_env_list(env_list);
	clear_history();
	exit(0);
}
