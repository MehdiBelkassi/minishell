/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:17:24 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 21:53:18 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	get_key_len(char *input, int start)
{
	int	i;

	i = start;
	if (input[start] == '$')
		return (1);
	if (input[start] == '?')
		return (1);
	if (input[start] == '{')
	{
		i++;
		while (input[i] && input[i] != '}')
			i++;
		if (input[i] == '}')
			i++;
		return (i - start);
	}
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	return (i - start);
}

char	*get_key_value(char *key, t_env *env, int exit_status)
{
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(exit_status));
	if (ft_isdigit(key[0]))
		return (ft_strjoin(ft_strdup(""), key + 1));
	if (env->key == NULL)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_key(char *input, int start, int key_len)
{
	int		i;
	char	*key;

	if (input[start] == '{')
	{
		key = malloc(key_len - 1);
		i = 0;
		while (i < key_len - 2)
		{
			key[i] = input[start + 1 + i];
			i++;
		}
	}
	else 
	{
		key = malloc(key_len + 1);
		i = 0;
		while (i < key_len)
		{
			key[i] = input[start + i];
			i++;
		}
	}
	return (key[i] = '\0', key);
}

char	*process_variable(char *input, int *i, t_env *env, int exit_status)
{
	char	*key;
	char	*value;
	char	*result;
	int		key_len;

	key_len = get_key_len(input, *i + 1);
	key = get_key(input, *i + 1, key_len);
	if (!key)
	{
		*i += key_len + 1;
		return (ft_strdup(""));
	}
	value = get_key_value(key, env, exit_status);
	if (!value)
		result = ft_strdup("");
	else
		result = ft_strdup(value);
	*i += key_len + 1;
	if (value && (ft_strcmp(key, "?") == 0 || ft_strcmp(key, "$") == 0
			|| ft_isdigit(key[0])))
		free(value);
	free(key);
	return (result);
}

char	*handle_variable_expansion(char *input, int *i, t_env *env,
	char *result)
{
	char	*var_value;

	var_value = process_variable(input, i, env, env->exit_status);
	if (var_value)
	{
		result = join_and_free(result, var_value);
		free(var_value);
	}
	return (result);
}
