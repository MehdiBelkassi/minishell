/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:33:05 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 21:32:07 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

t_env	*create_env_node(char *env_str)
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
	node->value = ft_strdup(env_str + i + 1);
	if (!node->value)
		return (NULL);
	node->exit_status = 0;
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*build_env_list(char **envp)
{
	t_env	*list;
	t_env	*node;
	int		i;

	i = 0;
	if (!envp || !envp[0])
	{
		list = malloc(sizeof(t_env));
		if (!list)
			return (NULL);
		list->key = NULL;
		list->value = NULL;
		list->exit_status = 0;
		list->next = NULL;
		return (list);
	}
	list = NULL;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (node)
			add_env_node(&list, node);
		i++;
	}
	return (list);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env && env->key != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
