/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:39:20 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 12:38:46 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	unset_it(char *key, t_env **env_list)
{
	t_env	*current;
	t_env	*perv;

	current = *env_list;
	perv = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (perv)
				perv->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		perv = current;
		current = current->next;
	}
}

void	print_error_unset(char *str)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	handle_unset(char **command, t_env **env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (command[0] && command[1])
	{
		while (command[i])
		{
			if (ft_strchr(command[i], '=') || check_args(command[i]))
			{
				print_error_unset(command[i]);
				flag = 1;
			}
			else
			{
				if (variable_exists(command[i], *env))
					unset_it(command[i], env);
			}
			i++;
		}
	}
	return (flag);
}
