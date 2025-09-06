/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:17:39 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/25 13:16:18 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_token_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_WORD,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				quotes;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token_type	get_token_type(char *value);
void			skip_spaces(char *cmd, int *i);
char			*strdup_operator(char *cmd, int *i);
char			if_quotes(char *value);
char			*strdup_word_with_quotes(char *cmd, int *i);
char			*ft_strdup(char *s1);
char			*remove_quotes(char *str);
int				is_operator(char *cmd, int i);
int				ft_isspace(char c);

#endif