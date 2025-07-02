/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:50:39 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/23 11:55:15 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_died(t_philo *philos)
{
	int			died;
	size_t		current_time;
	size_t		last_meal_time;
	int			eating_status;

	died = 0;
	sem_wait(philos->sem->eat_lock);
	current_time = get_time();
	last_meal_time = philos->last_meal;
	eating_status = philos->eating;
	sem_post(philos->sem->eat_lock);
	if (current_time - last_meal_time >= (size_t)philos->time_to_die
		&& eating_status == 0)
		died = 1;
	return (died);
}

int	check_philo_finished(t_philo *philo)
{
	int	finished;

	finished = 0;
	if (philo->max_eaten == -1)
		return (0);
	sem_wait(philo->sem->eat_lock);
	if (philo->num_eaten >= philo->max_eaten)
		finished = 1;
	sem_post(philo->sem->eat_lock);
	return (finished);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_philo_finished(philo))
			exit(0);
		if (check_died(philo))
		{
			sem_wait(philo->sem->write_lock);
			printf("%zu %d died\n", get_time() - philo->start,
				philo->philo_num);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

void	do_your_work(t_philo *philo)
{
	pthread_t	monitor_thread;

	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	if (pthread_create(&monitor_thread, NULL, death_monitor, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);
	while (1)
	{
		if (check_philo_finished(philo))
			exit(0);
		philo_is_eating(philo);
		if (check_philo_finished(philo))
			exit(0);
		philo_is_sleep(philo);
		philo_is_think(philo);
	}
}
