/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:10:44 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/22 19:32:43 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->write_lock);
	if (!philo->dead || check_died1(philo))
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	timestamp = get_time() - philo->start;
	printf("%zu %d %s\n", timestamp, philo->num, message);
	pthread_mutex_unlock(philo->write_lock);
}

int	check_died1(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		usleep(100);
	while (check_died1(philo) == 0)
	{
		philo_is_eating(philo);
		philo_is_sleep(philo);
		philo_is_think(philo);
	}
	return (ptr);
}

void	creat_threads(t_monitor *monitor, pthread_mutex_t *forks)
{
	pthread_t	mon;
	int			i;

	i = 0;
	if (pthread_create(&mon, NULL, &check_diedloop, monitor) != 0)
		return (ccclean(forks, monitor->philos), (void)0);
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_create(&monitor->philos[i].thread
				, NULL, &philo_routine, &monitor->philos[i]) != 0)
			return (ccclean(forks, monitor->philos),(void)0);
		i++;
	}
	if (pthread_join(mon, NULL) != 0)
		return (ccclean(forks, monitor->philos), (void)0);
	i = 0;
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
			return (ccclean(forks, monitor->philos), (void)0);
		i++;
	}
}
