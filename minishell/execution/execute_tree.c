/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:53:26 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 13:00:29 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	print_error_exec(char *str, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
}

int	execute_tree(t_tree *tree, t_env *env_list)
{
	if (!tree)
		return (0);
	if (tree->type == N_CMD)
		return (execute_command(tree, &env_list));
	else if (tree->type == N_PIPE)
		return (execute_pipe(tree, &env_list));
	else if (tree->type == N_RIDIR_IN || tree->type == N_RIDIR_OUT
		|| tree->type == N_APPEND || tree->type == N_HEREDOC)
		return (handle_redirections(tree, &env_list));
	return (0);
}
