/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:32:57 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/19 14:33:42 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	pars_is_operator(char *token)
{
	return (!ft_strcmp(token, "|") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<<"));
}

int	pars_is_redirection(char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}
