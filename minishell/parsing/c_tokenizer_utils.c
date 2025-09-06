/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tokenizer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:08:34 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/19 14:12:41 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	res = malloc(strlen(str) + 1);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	return (res[j] = '\0', res);
}

t_token_type	get_token_type(char *value)
{
	if (value[0] == '|' && value[1] == '\0')
		return (T_PIPE);
	if (value[0] == '>' && value[1] == '\0')
		return (T_REDIR_OUT);
	if (value[0] == '<' && value[1] == '\0')
		return (T_REDIR_IN);
	if (value[0] == '>' && value[1] == '>' && value[2] == '\0')
		return (T_APPEND);
	if (value[0] == '<' && value[1] == '<' && value[2] == '\0')
		return (T_HEREDOC);
	return (T_WORD);
}

char	if_quotes(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}
