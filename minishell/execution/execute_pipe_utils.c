/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:46:55 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 21:47:28 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	right_fork_error(int fd_0, int fd_1, t_env **env_list, pid_t pid_left)
{
	perror("fork: ");
	close(fd_0);
	close(fd_1);
	kill(pid_left, SIGTERM);
	signal(SIGINT, handle_sigint);
	(*env_list)->exit_status = 1;
	return (1);
}

int	left_fork_error(int fd_0, int fd_1, t_env **env_list)
{
	perror("fork: ");
	close(fd_0);
	close(fd_1);
	signal(SIGINT, handle_sigint);
	(*env_list)->exit_status = 1;
	return (1);
}
