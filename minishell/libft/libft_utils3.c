/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:59:09 by aben-moh          #+#    #+#             */
/*   Updated: 2025/07/23 20:22:08 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

void	*ft_memset(void *buffer, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)buffer;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (buffer);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	nbr_len(long nbr)
{
	unsigned int	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count++;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		str_len;
	long	nbr;
	char	*res;

	nbr = n;
	str_len = nbr_len(nbr);
	if (nbr == 0)
		return (ft_strdup("0"));
	res = malloc(sizeof(char) * (str_len + 1));
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = -nbr;
	}
	res[str_len] = '\0';
	while (nbr > 0)
	{
		res[str_len - 1] = nbr % 10 + 48;
		nbr = nbr / 10;
		str_len--;
	}
	return (res);
}
