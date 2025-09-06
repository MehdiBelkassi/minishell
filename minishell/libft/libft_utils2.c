/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:56:12 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/23 20:21:37 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	is_all_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strndup(char *s1, char c)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = -1;
	len = 0;
	while (s1[++i] != c)
		len++;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] != c)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
