/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:36:27 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/26 21:33:13 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

t_env	*create_env_node_equal(char *env_str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strndup(env_str, '\0');
	if (!node->key)
		return (NULL);
	node->value = NULL;
	node->next = NULL;
	return (node);
}

t_env	*create_env_special_node(char *env_str)
{
	t_env	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while (env_str[i] && env_str[i] != '=')
		i++;
	node->key = ft_strndup(env_str, '=');
	if (!node->key)
		return (NULL);
	node->value = strip_quotes(env_str + i + 1);
	if (!node->value)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	update_env_value(char *command, t_env **env_list)
{
	int		i;
	t_env	*temp;
	char	*key;
	char	*value;

	temp = *env_list;
	i = 0;
	while (command[i] && command[i] != '=')
		i++;
	if (!command[i])
		return ;
	key = ft_substr(command, 0, i);
	value = strip_quotes(command + i + 1);
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = value;
			break ;
		}
		temp = temp->next;
	}
	free(key);
}

void	add_to_list(char *command, t_env **env_list)
{
	t_env	*node;

	node = NULL;
	if (variable_exists(command, *env_list))
	{
		update_env_value(command, env_list);
	}
	else
	{
		if (check_equal(command) == 1)
			node = create_env_special_node(command);
		else
			node = create_env_node_equal(command);
		add_env_node(env_list, node);
	}
}

int	handle_export(char **command, t_env **env_list)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (command[0] && !command[1])
		return (print_export_list(*env_list), 0);
	else
	{
		while (command[i])
		{
			if (check_args(command[i]))
			{
				printf("bash: export: `%s': not a valid identifier\n",
					command[i]);
				flag = 1;
			}
			else
				add_to_list(command[i], env_list);
			i++;
		}
	}
	return (flag);
}
