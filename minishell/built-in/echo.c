/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:36:21 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 13:21:51 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

int	check_flags(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			while (str[i] == 'n' && str[i])
				i++;
			if (str[i] == '\0')
				return (1);
			else
				return (0);
		}
		else 
			return (0);
	}
	return (0);
}

int	echo_function(char **command)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (command[i] && check_flags(command[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (flag != 1)
		printf("\n");
	return (0);
}
