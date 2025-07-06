/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:22:49 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/07/04 20:04:11 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	current;
	size_t			timestamp;

	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec) * 1000 + (current.tv_usec / 1000);
	return (timestamp);
}

int	init_sem(t_semas **sms, int num_philos)
{
	*sms = malloc(sizeof(t_semas));
	if (!(*sms))
		return (-1);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/eat");
	sem_unlink("/dead");
	(*sms)->forks = sem_open("/forks", O_CREAT, 0644, num_philos);
	if ((*sms)->forks == SEM_FAILED)
		return (free(*sms), -1);
	(*sms)->deadlock = sem_open("/dead", O_CREAT, 0644, 1);
	if ((*sms)->deadlock == SEM_FAILED)
		return (free(*sms), sem_close((*sms)->forks), -1);
	(*sms)->eat_lock = sem_open("/eat", O_CREAT, 0644, 1);
	if ((*sms)->eat_lock == SEM_FAILED)
		return (free(*sms), sem_close((*sms)->forks)
			, sem_close((*sms)->deadlock), 1);
	(*sms)->write_lock = sem_open("/write", O_CREAT, 0644, 1);
	if ((*sms)->write_lock == SEM_FAILED)
	{
		free(*sms);
		sem_close((*sms)->forks);
		return (sem_close((*sms)->deadlock), sem_close((*sms)->eat_lock), -1);
	}
	return (0);
}

static void	init_philo_basic(t_philo *philo, char **av, int i)
{
	philo->num_of_philos = ft_atoi1(av[1]);
	philo->time_to_die = ft_atoi1(av[2]);
	philo->time_to_eat = ft_atoi1(av[3]);
	philo->time_to_sleep = ft_atoi1(av[4]);
	if (av[5])
		philo->max_eaten = ft_atoi1(av[5]);
	else
		philo->max_eaten = -1;
	philo->philo_num = i + 1;
}

static void	init_philo_state(t_philo *philo, t_semas *sms, size_t start_time)
{
	philo->eating = 0;
	philo->last_meal = start_time;
	philo->num_eaten = 0;
	philo->sem = sms;
	philo->start = start_time;
	philo->is_dead = 0;
}

t_philo	*init_philos(char **av)
{
	int		i;
	t_philo	*philos;
	t_semas	*sms;
	size_t	start_time;

	if (init_sem(&sms, ft_atoi1(av[1])) == -1)
		return (NULL);
	philos = (t_philo *)malloc((ft_atoi1(av[1]) * sizeof(t_philo)));
	if (!philos)
		return (NULL);
	start_time = get_time();
	i = 0;
	while (i < ft_atoi1(av[1]))
	{
		init_philo_basic(&philos[i], av, i);
		init_philo_state(&philos[i], sms, start_time);
		i++;
	}
	return (philos);
}
