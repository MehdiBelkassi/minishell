/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:32:20 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/23 16:46:39 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	print_export_list(t_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			printf("declare -x %s\n", env->key);
		else
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	check_args(char *command)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (command[0] != '_' && !ft_isalpha(command[0]))
	{
		flag = 1;
		return (flag);
	}
	while (command[i])
	{
		if (command[i] == '=')
			break ;
		if (!ft_isalnum(command[i]) && command[i] != '_')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	return (flag);
}

int	check_equal(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	variable_exists(char *command, t_env *env_list)
{
	t_env	*temp;
	char	*key;

	temp = env_list;
	if (check_equal(command))
		key = ft_strndup(command, '=');
	else
		key = ft_strndup(command, '\0');
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (free(key), 1);
		temp = temp->next;
	}
	free(key);
	return (0);
}

char	*strip_quotes(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '\"') && str[len - 1] == str[0])
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
