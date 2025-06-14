/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:46:43 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 16:07:28 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				num;
	int				num_of_philos;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				num_to_eat;
	int				eating;
	int				meals_eaten;
	int				*dead;
	size_t			last_meal;
	size_t			start;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;

}	t_philo;

typedef struct s_monitor
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_monitor;

int		test_parsing(char **av, int ac);
long	ft_atoi(char *str);
void	init_philos(t_philo *philo, char **argv,
			pthread_mutex_t *forks, t_monitor *monitor);
void	init_forks(pthread_mutex_t *forks, int num);
void	init_monitor(t_monitor *t, t_philo *philos);
int		check_died(t_philo *philos);
void	*check_diedloop(void *ptr);
void	ccclean(pthread_mutex_t *forks, t_philo *philos);
size_t	get_time(void);
void	philo_is_think(t_philo *philo);
void	philo_is_sleep(t_philo *philo);
void	philo_is_eating(t_philo *philo);
void	print_message(t_philo *philo, char *message);
void	creat_threads(t_monitor *monitor, pthread_mutex_t *forks);
void	ft_usleep(int time, t_philo *philo);
void	*philo_routine(void *ptr);
int		check_died1(t_philo *philo);

#endif