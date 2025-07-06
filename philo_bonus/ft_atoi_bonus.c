/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:21:14 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/07/04 20:05:56 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi1(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' && str[i + 1] != '0')
		return (-1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		return (-1);
	return (result);
}

int	test_parsing(char **av, int ac)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid Arguments\n", 19);
		return (-1);
	}
	while (av[i])
	{
		if (ft_atoi1(av[i]) < 0 || ft_atoi1(av[i]) > INT_MAX)
		{
			write(2, "Invalid Arguments\n", 19);
			return (-1);
		}
		i++;
	}
	if ((av[5] && ft_atoi1(av[5]) == 0) || (ft_atoi1(av[1]) == 0))
		return (-1);
	return (0);
}
