/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:36:23 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/20 18:23:46 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_monitor(t_monitor *t, t_philo *philos)
{
	t->dead_flag = 0;
	t->philos = philos;
	pthread_mutex_init(&(t->dead_lock), NULL);
	pthread_mutex_init(&(t->meal_lock), NULL);
	pthread_mutex_init(&(t->write_lock), NULL);
}

void	init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "Error initializing fork mutex\n", 30);
			return ;
		}
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
	init_monitor(&monitor, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, av, forks, &monitor);
	creat_threads(&monitor, forks);
	free(forks);
	free(philos);
	return (0);
}
