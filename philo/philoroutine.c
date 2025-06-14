/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:29 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 16:12:00 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_think(t_philo *philo)
{
	if (check_died1(philo))
		return ;
	print_message(philo, "is thinking");
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
	if (check_died1(philo))
		return ;
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}

static void	take_forks(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		if (philo->num_of_philos == 1)
		{
			ft_usleep(philo->time_to_die, philo);
			pthread_mutex_unlock(philo->lfork);
			return ;
		}
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
	}
}

void	philo_is_eating(t_philo *philo)
{
	if (check_died1(philo))
		return ;
	take_forks(philo);
	if (philo->num_of_philos == 1)
		return ;
	philo->eating = 1;
	print_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}
