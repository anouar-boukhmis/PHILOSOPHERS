/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:36:23 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/22 20:12:21 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_monitor(t_monitor *t, t_philo *philos)
{
	t->dead_flag = 0;
	t->philos = philos;
	if (pthread_mutex_init(&(t->dead_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(t->meal_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(t->dead_lock));
		return (1);
	}
	if (pthread_mutex_init(&(t->write_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(t->dead_lock));
		pthread_mutex_destroy(&(t->meal_lock));
		return (1);
	}
	return (0);
}

int	init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	clean_monitor(t_monitor *monitor)
{
	pthread_mutex_destroy(&monitor->write_lock);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->meal_lock);
}

void	clean_all(t_monitor *mon, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	clean_monitor(mon);
	while (i < mon->philos->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_monitor		monitor;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (test_parsing(av, ac) == -1)
		return (1);
	forks = (pthread_mutex_t *)malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	philos = (t_philo *)malloc(ft_atoi(av[1]) * sizeof(t_philo));
	if (!philos)
		return (free(forks), 0);
	if (init_monitor(&monitor, philos))
		return (free(forks), free(philos), write(2, "MUTEX ERROR\n", 17), 1);
	if (init_forks(forks, ft_atoi(av[1])) == -1)
	{
		clean_monitor(&monitor);
		return (free(forks), free(philos), write(2, "MUTEX ERROR\n", 17), 1);
	}
	init_philos(philos, av, forks, &monitor);
	creat_threads(&monitor, forks);
	clean_all(&monitor, forks);
	free(forks);
	free(philos);
	return (0);
}
