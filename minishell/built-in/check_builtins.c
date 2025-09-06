/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:55:20 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/24 18:22:50 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	execute_builtin(t_tree *t_tree, t_env **env_list)
{
	if (ft_strcmp(t_tree->cmd[0], "echo") == 0)
		(*env_list)->exit_status = echo_function(t_tree->cmd);
	else if (ft_strcmp(t_tree->cmd[0], "pwd") == 0)
		(*env_list)->exit_status = print_pwd();
	else if (ft_strcmp(t_tree->cmd[0], "env") == 0)
		(*env_list)->exit_status = get_the_env(t_tree->cmd, *env_list);
	else if (ft_strcmp(t_tree->cmd[0], "exit") == 0)
		(*env_list)->exit_status = exit_hadi(t_tree->cmd);
	else if (ft_strcmp(t_tree->cmd[0], "export") == 0)
		(*env_list)->exit_status = handle_export(t_tree->cmd, env_list);
	else if (ft_strcmp(t_tree->cmd[0], "unset") == 0)
		(*env_list)->exit_status = handle_unset(t_tree->cmd, env_list);
	else if (ft_strcmp(t_tree->cmd[0], "cd") == 0)
		(*env_list)->exit_status = handle_cd(t_tree->cmd, env_list);
	return ((*env_list)->exit_status);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}
