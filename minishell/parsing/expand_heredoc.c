/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:22:33 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/26 18:54:32 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

char	*expand_var_heredoc(char *input, t_env *env)
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
			&& input[i] == '$'
			&& (input[i + 1] == '\"' || input[i + 1] == '\''))
			result = handle_dollar_quote(result, input[i], &i);
		else if (input[i] == '$' && input[i + 1])
			result = handle_variable_expansion(input, &i, env, result);
		else
			result = append_char(result, input[i++]);
	}
	return (result);
}

char	*expand_cmd_heredoc(char *input, t_env *env)
{
	char	*expanded;

	if (!input || !*input)
		return (NULL);
	expanded = expand_var_heredoc(input, env);
	if (!expanded)
		return (NULL);
	return (expanded);
}
