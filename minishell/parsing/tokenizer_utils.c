/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:47:00 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/19 14:35:38 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char	*strdup_operator(char *cmd, int *i)
{
	char	*str;

	if ((cmd[*i] == '>' && cmd[*i + 1] == '>')
		|| (cmd[*i] == '<' && cmd[*i + 1] == '<'))
	{
		str = malloc(3);
		str[0] = cmd[*i];
		str[1] = cmd[*i + 1];
		str[2] = '\0';
		(*i) += 2;
	}
	else
	{
		str = malloc(2);
		str[0] = cmd[*i];
		str[1] = '\0';
		(*i)++;
	}
	return (str);
}

int	is_operator(char *cmd, int i)
{
	if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		return (1);
	return (0);
}

char	*strdup_word_with_quotes(char *cmd, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (cmd[*i] && !ft_isspace(cmd[*i]) && !is_operator(cmd, *i))
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"')
		{
			quote = cmd[(*i)++];
			while (cmd[*i] && cmd[*i] != quote)
				(*i)++;
			if (cmd[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_substr(cmd, start, *i - start));
}
