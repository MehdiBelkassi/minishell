/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:50:08 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 21:47:25 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	handle_left_child(int *fd, t_tree *tree, t_env **env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_tree(tree->left, *env_list);
	exit((*env_list)->exit_status);
}

void	handle_right_child(int *fd, t_tree *tree, t_env **env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_tree(tree->right, *env_list);
	exit((*env_list)->exit_status);
}

void	handle_wait_and_status(pid_t pid_right, t_env **env_list)
{
	int	status;

	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		(*env_list)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			(*env_list)->exit_status = 130;
		if (WTERMSIG(status) == SIGQUIT)
			(*env_list)->exit_status = 131;
		printf("\n");
	}
}

int	execute_pipe(t_tree *tree, t_env **env_list)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return ((*env_list)->exit_status = 1, 1);
	}
	signal(SIGINT, SIG_IGN);
	pid_left = fork();
	if (pid_left == -1)
		return (left_fork_error(fd[0], fd[1], env_list));
	if (pid_left == 0)
		handle_left_child(fd, tree, env_list);
	pid_right = fork();
	if (pid_right == -1)
		return (right_fork_error(fd[0], fd[1], env_list, pid_left));
	if (pid_right == 0)
		handle_right_child(fd, tree, env_list);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	handle_wait_and_status(pid_right, env_list);
	return (signal(SIGINT, handle_sigint), 0);
}
