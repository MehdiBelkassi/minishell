/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 07:26:15 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 22:29:06 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	*check_cwd(char *cmd, char *cwd)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(cwd, "/");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	if (access(cmd_path, X_OK) == 0)
	{
		free(cwd);
		return (cmd_path);
	}
	free(cmd_path);
	free(cwd);
	return (NULL);
}

char	*get_path(char *cmd, t_env **env)
{
	char	*path_value;
	char	**paths;
	char	*result;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	result = check_direct_path(cmd);
	if (result || !cwd)
	{
		if (cwd)
			free(cwd);
		return (result);
	}
	path_value = get_env_value(*env, "PATH");
	if (!path_value)
		return (check_cwd(cmd, cwd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (free(cwd), NULL);
	result = search_in_paths(paths, cmd, cwd);
	if (result)
		return (result);
	free(cwd);
	free_array(paths);
	return (NULL);
}

int	count_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_list_to_array(t_env *env)
{
	char	**env_array;
	char	*key_equal;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	env_array = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		if (tmp->value)
		{
			key_equal = ft_strjoin(tmp->key, "=");
			env_array[i] = ft_strjoin(key_equal, tmp->value);
			free(key_equal);
			i++;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
