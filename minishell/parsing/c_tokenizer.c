/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:04:11 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 12:01:01 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	check_empty_tokens(char *tokens)
{
	if (!tokens)
		return (0);
	if (tokens[0] != '\0')
		return (1);
	return (0);
}

t_token	*new_token(char *value, int flag, int *expanded, t_env *env)
{
	t_token	*token;
	char	*expanded_cmd;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	expanded_cmd = NULL;
	token->quotes = if_quotes(value);
	if (flag == 0)
	{
		expanded_cmd = expand_cmd(value, env);
		if (!check_empty_tokens(expanded_cmd))
			*expanded = 1;
		token->value = remove_quotes(expanded_cmd);
		free(expanded_cmd);
	}
	else
		token->value = remove_quotes(value);
	if (!token->value)
		return (free(token), NULL);
	token->type = get_token_type(value);
	token->next = NULL;
	return (token);
}

void	add_tokens(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	update_flag(t_token *node)
{
	if (node->type == T_HEREDOC)
		return (1);
	return (0);
}

t_token	*convert_tokens(char **str_token, t_env *env)
{
	t_token	*token_list;
	t_token	*new_node;
	int		i;
	int		flag;
	int		expanded;

	if (!str_token)
		return (NULL);
	token_list = NULL;
	new_node = NULL;
	i = 0;
	flag = 0;
	while (str_token[i])
	{
		expanded = 0;
		new_node = new_token(str_token[i], flag, &expanded, env);
		flag = update_flag(new_node);
		if (expanded != 1)
			add_tokens(&token_list, new_node);
		else
			free_token_list(new_node);
		i++;
	}
	return (token_list);
}
