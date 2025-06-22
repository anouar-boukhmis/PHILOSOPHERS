/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:46:57 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/22 16:03:03 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(int time_ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < (size_t)time_ms)
		usleep(333);
}

void	cleanup_semaphores(t_semas *sem)
{
	if (sem)
	{
		if (sem->forks != SEM_FAILED)
		{
			sem_close(sem->forks);
			sem_unlink("/forks");
		}
		if (sem->write_lock != SEM_FAILED)
		{
			sem_close(sem->write_lock);
			sem_unlink("/write");
		}
		if (sem->eat_lock != SEM_FAILED)
		{
			sem_close(sem->eat_lock);
			sem_unlink("/eat");
		}
		if (sem->deadlock != SEM_FAILED)
		{
			sem_close(sem->deadlock);
			sem_unlink("/dead");
		}
		free (sem);
	}
}

void	handle_died(t_philo *philo)
{
	sem_wait(philo->sem->write_lock);
	printf("%zu %d died\n", get_time() - philo->start, philo->philo_num);
	exit(1);
}
