/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:27:11 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/24 12:01:45 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	check_p_r(char **tokens)
{
	int	i;

	if (!ft_strcmp(tokens[0], "|"))
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (pars_is_operator(tokens[i]))
		{
			if (!tokens[i + 1])
				return (0);
			if (!ft_strcmp(tokens[i], "|") && !ft_strcmp(tokens[i + 1], "|"))
				return (0);
			if (pars_is_redirection(tokens[i])
				&& pars_is_operator(tokens[i + 1]))
				return (0);
		}
		i++;
	}
	if (i > 0 && !ft_strcmp(tokens[i - 1], "|"))
		return (0);
	return (1);
}

int	check_quotes(char *cmd, int *flag)
{
	char	c;
	char	*end;

	end = cmd + ft_strlen(cmd);
	while (cmd < end)
	{
		c = *cmd;
		if (c == '\"' || c == '\'')
		{
			*flag = 1;
			cmd++;
			while (cmd < end && *cmd != c)
				cmd++;
			if (*cmd != c)
				return (0);
		}
		cmd++;
	}
	return (1);
}

int	check_echo(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == 'e' && cmd[i + 1] == 'c'
			&& cmd[i + 2] == 'h' && cmd[i + 3] == 'o')
			return (1);
		i++;
	}
	return (0);
}

int	pars(char **cmd, t_env *env)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 1;
	flag = 0;
	while (cmd[i])
	{
		if (!check_quotes(cmd[i], &flag))
			return (env->exit_status = 258, 0);
		if (check_echo(cmd[j - 1]) == 0 && flag == 0)
		{
			if (!check_p_r(cmd))
				return (env->exit_status = 258, 0);
		}
		j++;
		i++;
	}
	return (1);
}
