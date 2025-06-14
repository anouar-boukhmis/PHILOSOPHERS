/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:14:58 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 15:15:35 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ccclean(pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philos->write_lock);
	pthread_mutex_destroy(philos->dead_lock);
	pthread_mutex_destroy(philos->meal_lock);
	while (i < philos->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	write(2, "Error in Thread\n", 16);
}
