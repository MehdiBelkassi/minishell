/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:36:24 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/26 21:40:18 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	print_error_cd(void)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(" \n", 2);
}

void	update_env(char *value, char *key, t_env **env_list)
{
	t_env	*temp;
	char	*cwd;
	char	*temp_cwd;
	char	*dup_value;

	temp = *env_list;
	cwd = NULL;
	temp_cwd = NULL;
	if (temp->key == NULL)
		return ;
	dup_value = ft_strdup(value);
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = dup_value;
			break ;
		}
		temp = temp->next;
	}
	temp_cwd = ft_strjoin(key, "=");
	cwd = ft_strjoin_free(temp_cwd, dup_value);
	add_to_list(cwd, env_list);
	free(cwd);
}

int	go_to_dir(char *command, char *old_pwd, t_env **env_list)
{
	char	*dir;
	char	cwd[1024];
	char	*new_cwd;

	if (ft_strcmp(command, "HOME") == 0)
	{
		dir = get_env_value(*env_list, "HOME");
		if (!dir)
			return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	}
	else
		dir = command;
	if (chdir(dir) == -1)
		return (print_error_cd(), 1);
	if (!getcwd(cwd, 1024))
		return (perror("getcwd"), 1);
	new_cwd = ft_strdup(cwd);
	update_env(new_cwd, "PWD", env_list);
	update_env(old_pwd, "OLDPWD", env_list);
	free(new_cwd);
	return (0);
}

int	get_argc(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

int	handle_cd(char **command, t_env **env_list)
{
	char	*cwd;
	int		flag;
	int		argc;

	argc = get_argc(command);
	flag = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	if (!cwd)
		return (perror("getcwd"), 1);
	if (argc == 1)
		flag = go_to_dir("HOME", cwd, env_list);
	else
		flag = go_to_dir(command[1], cwd, env_list);
	free(cwd);
	return (flag);
}
