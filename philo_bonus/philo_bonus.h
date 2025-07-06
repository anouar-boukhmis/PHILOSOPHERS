/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:53:49 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/07/03 20:41:05 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <pthread.h>
# include <fcntl.h>

typedef struct s_semas
{
	sem_t	*write_lock;
	sem_t	*eat_lock;
	sem_t	*deadlock;
	sem_t	*forks;
}	t_semas;

typedef struct s_philo
{
	int		philo_num;
	pid_t	pid;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		num_of_philos;
	size_t	last_meal;
	int		eating;
	int		num_eaten;
	int		max_eaten;
	int		is_dead;
	size_t	start;
	t_semas	*sem;
}	t_philo;

typedef struct s_monitor
{
	t_philo	*philos;
	int		status;
	int		is_dead;
}	t_monitor;

long	ft_atoi1(char *str);
int		test_parsing(char **av, int ac);
t_philo	*init_philos(char **av);
size_t	get_time(void);
int		check_died(t_philo *philos);
void	philo_is_eating(t_philo *philo);
void	philo_is_sleep(t_philo *philo);
void	philo_is_think(t_philo *philo);
int		check_all_philos_eat(t_philo *philos);
void	print_message(t_philo *philo, char *message);
int		check_philo_finished(t_philo *philo);
void	do_your_work(t_philo *philo);
void	handle_died(t_philo *philo);
void	ft_usleep(int time_ms);
void	cleanup_semaphores(t_semas *sem);
void	handle_died(t_philo *philo);
void	check_phi(t_philo *philo);

#endif