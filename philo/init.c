/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:27:23 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 16:13:01 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	current;
	size_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec) * 1000 + (current.tv_usec / 1000);
	return (timestamp);
}

static void	init_philo_basic(t_philo *philo, char **argv, int i)
{
	philo[i].num = i + 1;
	philo[i].eating = 0;
	philo[i].meals_eaten = 0;
	philo[i].num_of_philos = ft_atoi(argv[1]);
	philo[i].time_to_die = ft_atoi(argv[2]);
	philo[i].time_to_eat = ft_atoi(argv[3]);
	philo[i].time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo[i].num_to_eat = ft_atoi(argv[5]);
	else
		philo[i].num_to_eat = -1;
}

static void	init_philo_locks(t_philo *philo, t_monitor *monitor, int i)
{
	philo[i].dead_lock = &(monitor->dead_lock);
	philo[i].write_lock = &(monitor->write_lock);
	philo[i].meal_lock = &(monitor->meal_lock);
	philo[i].start = get_time();
	philo[i].last_meal = get_time();
	philo[i].dead = &monitor->dead_flag;
}

static void	init_philo_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	philo[i].lfork = &forks[i];
	if (i == 0)
		philo[i].rfork = &forks[philo[i].num_of_philos - 1];
	else
		philo[i].rfork = &forks[i - 1];
}

void	init_philos(t_philo *philo, char **argv, pthread_mutex_t *forks,
		t_monitor *monitor)
{
	int	i;

	i = 0;
	monitor->dead_flag = 0;
	while (i < ft_atoi(argv[1]))
	{
		init_philo_basic(philo, argv, i);
		init_philo_locks(philo, monitor, i);
		init_philo_forks(philo, forks, i);
		i++;
	}
}
