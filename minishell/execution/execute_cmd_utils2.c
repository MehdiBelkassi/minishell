/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:18:38 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 15:26:10 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	check_empty_command(t_tree *tree, char **envp, t_env **env_list)
{
	if (!tree->cmd || !tree->cmd[0] || tree->cmd[0][0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		free_array(envp);
		return ((*env_list)->exit_status = 127);
	}
	return (0);
}

int	handle_builtin(t_tree *tree, char **envp, t_env **env_list)
{
	(*env_list)->exit_status = execute_builtin(tree, env_list);
	free_array(envp);
	return ((*env_list)->exit_status);
}

int	check_dot_command(t_tree *tree, char **envp, t_env **env_list)
{
	if (strcmp(tree->cmd[0], ".") == 0 && tree->cmd[1] == NULL)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		free_array(envp);
		return ((*env_list)->exit_status = 2);
	}
	return (0);
}

char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

char	*search_in_paths(char **paths, char *cmd, char *cwd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			free(cwd);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}
