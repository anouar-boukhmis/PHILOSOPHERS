/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:03:05 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/07/03 20:41:58 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *philo, char *message)
{
	size_t	timestamp;

	sem_wait(philo->sem->write_lock);
	timestamp = get_time() - philo->start;
	printf("%zu %d %s\n", timestamp, philo->philo_num, message);
	sem_post(philo->sem->write_lock);
}

void	philo_is_sleep(t_philo *philo)
{
	sem_wait(philo->sem->write_lock);
	if (check_died(philo) || check_philo_finished(philo))
		return (sem_post(philo->sem->write_lock), (void)0);
	sem_post(philo->sem->write_lock);
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_is_think(t_philo *philo)
{
	sem_wait(philo->sem->write_lock);
	if (check_died(philo) || check_philo_finished(philo))
		return (sem_post(philo->sem->write_lock), (void)0);
	sem_post(philo->sem->write_lock);
	print_message(philo, "is thinking");
}

static void	handle_single_philo(t_philo *philo)
{
	sem_wait(philo->sem->forks);
	print_message(philo, "has taken a fork");
	ft_usleep(philo->time_to_die);
	sem_post(philo->sem->forks);
}

void	philo_is_eating(t_philo *philo)
{
	if (check_died(philo) || check_philo_finished(philo))
		return ;
	if (philo->num_of_philos == 1)
		return (handle_single_philo(philo), (void)0);
	sem_wait(philo->sem->forks);
	print_message(philo, "has taken a fork");
	check_phi(philo);
	sem_wait(philo->sem->forks);
	print_message(philo, "has taken a fork");
	sem_wait(philo->sem->eat_lock);
	philo->eating = 1;
	philo->last_meal = get_time();
	sem_post(philo->sem->eat_lock);
	print_message(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->sem->eat_lock);
	philo->eating = 0;
	philo->num_eaten++;
	sem_post(philo->sem->eat_lock);
	sem_post(philo->sem->forks);
	sem_post(philo->sem->forks);
	if (philo->num_eaten == philo->max_eaten)
		exit (0);
}
