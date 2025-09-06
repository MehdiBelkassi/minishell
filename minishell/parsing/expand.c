/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:19:44 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/24 13:41:24 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

char	*append_char(char *str, char c)
{
	char	temp[2];
	char	*result;

	temp[0] = c;
	temp[1] = '\0';
	if (!str)
		result = ft_strdup(temp);
	else
		result = ft_strjoin(str, temp);
	free(str);
	return (result);
}

int	update_quote_state(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && !(*double_quote))
	{
		*single_quote = !(*single_quote);
		return (1);
	}
	else if (c == '\"' && !(*single_quote))
	{
		*double_quote = !(*double_quote);
		return (1);
	}
	return (0);
}

char	*handle_dollar_quote(char *result, char c, int *i)
{
	result = append_char(result, c);
	(*i)++;
	return (result);
}

char	*expand_var(char *input, t_env *env)
{
	char	*result;
	int		i;
	int		single_quote;
	int		double_quote;

	if (!input)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i] && result)
	{
		if (update_quote_state(input[i], &single_quote, &double_quote))
			result = append_char(result, input[i++]);
		else if ((single_quote || double_quote)
			&& input[i] == '$' && input[i + 1] == '\"')
			result = handle_dollar_quote(result, input[i], &i);
		else if (input[i] == '$' && !single_quote && input[i + 1])
			result = handle_variable_expansion(input, &i, env, result);
		else
			result = append_char(result, input[i++]);
	}
	return (result);
}

char	*expand_cmd(char *input, t_env *env)
{
	char	*expanded;

	if (!input || !*input)
		return (NULL);
	expanded = expand_var(input, env);
	if (!expanded)
		return (NULL);
	return (expanded);
}
