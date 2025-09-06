/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-moh <aben-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:39:14 by mbelkass          #+#    #+#             */
/*   Updated: 2025/07/25 12:35:54 by aben-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../par.h"

long long	ft_atoi(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", str);
			exit(255);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	is_a_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	exit_for_norm(char **command)
{
	long long	number;

	number = ft_atoi(command[1]);
	if (number < 0)
		number = (unsigned int)number;
	printf("exit\n");
	exit(number % 256);
}

void	print_error(char *str)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	exit_hadi(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (i == 1)
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_a_number(command[1]))
	{
		print_error(command[1]);
		exit(255);
	}
	if (i > 2)
	{
		ft_atoi(command[1]);
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return (1);
	}
	exit_for_norm(command);
	return (0);
}
