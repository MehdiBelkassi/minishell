/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:06:15 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/24 18:39:09 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static char	**ft_free_split(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**ft_put_words(char **str, char *s, char c, int nb)
{
	int	start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
	while (j < nb)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		str[j] = ft_substr(s, start, i - start);
		if (!str[j])
			return (ft_free_split(str, j));
		j++;
	}
	str[j] = 0;
	return (str);
}

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && (s[i] != c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**res;

	if (s == NULL)
		return (NULL);
	res = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	if (!ft_put_words(res, s, c, ft_count_words(s, c)))
		return (NULL);
	return (res);
}
