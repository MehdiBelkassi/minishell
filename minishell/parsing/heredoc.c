/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:57 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 18:25:27 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	heredoc_sig(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

char	*generate_file_name(void)
{
	char		*num;
	char		*filename;
	static int	count;

	num = ft_itoa(++count);
	filename = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (filename);
}

void	read_content(char *delimiter, int fd, int flag, t_env *env)
{
	char		*line;

	while (1)
	{
		signal(SIGINT, heredoc_sig);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		if (flag == 0)
			line = expand_cmd_heredoc(line, env);
		if (line && line[0] != '\0')
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	exit(0);
}

int	read_heredoc_content(char *delimiter, int flag, t_env *env)
{
	char			*filename;
	int				status;
	int				fd[2];
	pid_t			pid;
	struct termios	term;

	filename = generate_file_name();
	fd[0] = open(filename, O_CREAT | O_RDWR, 0644);
	fd[1] = open(filename, O_RDWR, 0644);
	tcgetattr(STDIN_FILENO, &term);
	unlink(filename);
	free(filename);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		read_content(delimiter, fd[0], flag, env);
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (WEXITSTATUS(status) == 1)
	{
		signal(SIGINT, handle_sigint);
		return (close(fd[1]), free(delimiter), -1);
	}
	signal(SIGINT, handle_sigint);
	return (close(fd[0]), free(delimiter), fd[1]);
}
