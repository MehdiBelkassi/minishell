/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:05:02 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/26 18:56:00 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	has_valid_command(t_tree *tree)
{
	if (!tree)
		return (0);
	if (tree->type == N_CMD && tree->cmd && tree->cmd[0] 
		&& tree->cmd[0][0] != '\0')
		return (1);
	if (tree->type != N_CMD)
		return (1);
	return (0);
}

int	handle_exec_input(t_tree *tree, int fd, int temp_fd_in, t_env **env_list)
{
	int	flag;

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		(*env_list)->exit_status = 1;
		return (1);
	}
	close(fd);
	if (has_valid_command(tree->left))
		flag = execute_tree(tree->left, *env_list);
	else
		flag = 0;
	dup2(temp_fd_in, STDIN_FILENO);
	close(temp_fd_in);
	return (flag);
}

int	handle_exec_output(t_tree *tree, int fd, int temp_fd_out, t_env **env_list)
{
	int	flag;

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		(*env_list)->exit_status = 1;
		return (1);
	}
	close(fd);
	if (has_valid_command(tree->left))
		flag = execute_tree(tree->left, *env_list);
	else
		flag = 0;
	dup2(temp_fd_out, STDOUT_FILENO);
	close(temp_fd_out);
	return (flag);
}

int	open_filename(char *filename, int type)
{
	int	fd;

	fd = 0;
	if (type == N_RIDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == N_RIDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == N_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	handle_redirections(t_tree *tree, t_env **env_list)
{
	int	fd_in;
	int	fd_out;
	int	fd;

	fd_out = dup(1);
	fd_in = dup(0);
	if (tree->type != N_HEREDOC)
		fd = open_filename(tree->filename, tree->type);
	else
	{
		if (tree->fd == -1)
			return ((*env_list)->exit_status = 1, 1);
		fd = tree->fd;
	}
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tree->filename, 2);
		return (perror(" "), (*env_list)->exit_status = 1, 1);
	}
	if (tree->type == N_RIDIR_IN || tree->type == N_HEREDOC)
		return (close(fd_out), handle_exec_input(tree, fd, fd_in, env_list));
	else if (tree->type == N_RIDIR_OUT || tree->type == N_APPEND)
		return (close(fd_in), handle_exec_output(tree, fd, fd_out, env_list));
	return (0);
}
