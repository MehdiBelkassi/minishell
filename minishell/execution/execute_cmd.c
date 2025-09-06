/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:55:22 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 16:27:26 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	cleanup_exit(char **envp, char *path, int exit_code)
{
	free_array(envp);
	free(path);
	exit(exit_code);
}

void	handle_child_process(char *path, t_tree *tree, char **envp)
{
	struct stat	st;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (stat(path, &st) == -1)
	{
		print_error_exec(": No such file or directory\n", tree->cmd[0]);
		cleanup_exit(envp, path, 127);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_error_exec(": Is a directory\n", tree->cmd[0]);
		cleanup_exit(envp, path, 126);
	}
	if (access(path, X_OK) == -1)
	{
		perror("minishell");
		cleanup_exit(envp, path, 126);
	}
	execve(path, tree->cmd, envp);
	perror("minishell");
	cleanup_exit(envp, path, 127);
}

void	handle_parent_process(pid_t pid, t_env **env_list, struct termios term)
{
	int	status;

	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (WIFEXITED(status))
		(*env_list)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("\n");
			(*env_list)->exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit\n");
			(*env_list)->exit_status = 131;
		}
	}
}

int	fork_and_execute(char *path, t_tree *tree, char **envp, t_env **env_list)
{
	pid_t			pid;
	struct termios	term;

	signal(SIGINT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &term);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_array(envp);
		free(path);
		return (-1);
	}
	else if (pid == 0)
		handle_child_process(path, tree, envp);
	else
		handle_parent_process(pid, env_list, term);
	signal(SIGINT, handle_sigint);
	return (0);
}

int	execute_command(t_tree *tree, t_env **env_list)
{
	char	*path;
	char	**envp;
	int		result;

	envp = env_list_to_array(*env_list);
	result = check_empty_command(tree, envp, env_list);
	if (result)
		return (result);
	if (is_builtin(tree->cmd[0]))
		return (handle_builtin(tree, envp, env_list));
	result = check_dot_command(tree, envp, env_list);
	if (result)
		return (result);
	path = get_path(tree->cmd[0], env_list);
	if (!path && !ft_strchr(tree->cmd[0], '/'))
	{
		print_error_exec(": command not found\n", tree->cmd[0]);
		free_array(envp);
		return ((*env_list)->exit_status = 127);
	}
	if (!path)
		path = ft_strdup(tree->cmd[0]);
	result = fork_and_execute(path, tree, envp, env_list);
	return (free_array(envp), free(path), result);
}
