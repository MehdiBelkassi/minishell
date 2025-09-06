/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:25:09 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 12:53:50 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	check_if_ambiguous(char *filename)
{
	int	i;

	i = 0;
	if (filename[0] == '\0')
		return (0);
	while (filename[i])
	{
		if (filename[i] == ' ')
		{
			while (filename[i] == ' ')
				i++;
			if (filename[i] != '\0')
				return (0);
			else if (filename[i] == '\0')
				break ;
		}
		i++;
	}
	return (1);
}

int	check_ambiguous(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_REDIR_IN || tokens->type == T_REDIR_OUT
			|| tokens->type == T_APPEND)
		{
			if (tokens->next->quotes == 0
				&& !check_if_ambiguous(tokens->next->value))
			{
				ft_putstr_fd("bash: ambiguous redirect", 2);
				printf("\n");
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
