/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:34:22 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 12:53:11 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	skip_spaces(char *cmd, int *i)
{
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
}

char	**ft_token(char *cmd, t_env *env)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = malloc(sizeof(char *) * (ft_strlen(cmd) + 1));
	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		skip_spaces(cmd, &i);
		if (cmd[i] == '\0')
			break ;
		if (is_operator(cmd, i))
			tokens[j] = strdup_operator(cmd, &i);
		else
			tokens[j] = strdup_word_with_quotes(cmd, &i);
		j++;
	}
	tokens[j] = NULL;
	if (!pars(tokens, env))
	{
		ft_putstr_fd("bash: syntax error\n", 2);
		return (free_array(tokens), NULL);
	}
	return (tokens);
}
