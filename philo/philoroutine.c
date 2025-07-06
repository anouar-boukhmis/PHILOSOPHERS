/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:29 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/07/04 19:38:30 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_think(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), (void)0);
	pthread_mutex_unlock(philo->dead_lock);
	print_message(philo, "is thinking", 0);
}

void	ft_usleep(int time_ms, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < (size_t)time_ms && !check_died1(philo))
		usleep(333);
}

void	philo_is_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), (void)0);
	pthread_mutex_unlock(philo->dead_lock);
	print_message(philo, "is sleeping", 0);
	ft_usleep(philo->time_to_sleep, philo);
}

static void	take_forks(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork", 0);
		if (philo->num_of_philos == 1)
		{
			ft_usleep(philo->time_to_die + 4, philo);
			pthread_mutex_unlock(philo->lfork);
			return ;
		}
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork", 0);
	}
}

void	philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
		return (pthread_mutex_unlock(philo->dead_lock), (void)0);
	pthread_mutex_unlock(philo->dead_lock);
	take_forks(philo);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		return ;
	}
	philo->eating = 1;
	print_message(philo, "is eating", 0);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}
