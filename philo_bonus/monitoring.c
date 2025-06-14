/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:50:39 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 18:02:28 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_died(t_philo *philos)
{
	int	died;

	died = 0;
	sem_wait(philos->sem->eat_lock);
	if (get_time() - philos->last_meal >= (size_t)philos->time_to_die
		&& philos->eating == 0)
		died = 1;
	sem_post(philos->sem->eat_lock);
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

void	do_your_work(t_philo *philo)
{
	while (1)
	{
		if (check_died(philo))
			handle_died(philo);
		philo_is_eating(philo);
		if (check_died(philo))
			handle_died(philo);
		philo_is_sleep(philo);
		if (check_died(philo))
			handle_died(philo);
		philo_is_think(philo);
	}
}
