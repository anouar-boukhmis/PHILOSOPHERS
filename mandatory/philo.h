/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:46:43 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/04/02 19:52:50 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

typedef struct s_monitor
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_monitor;


typedef struct s_philo
{
    pthread_t thread;
    int num;//
    int num_of_philos;//
    int time_to_sleep;//
    int time_to_eat;//
    int time_to_die;//
    int num_to_eat;//
    int eating;//
    int meals_eaten;//
    pthread_mutex_t *rfork;//
    pthread_mutex_t *lfork;//
    pthread_mutex_t *dead_lock;//
	pthread_mutex_t *meal_lock;//
	pthread_mutex_t *write_lock;//

} t_philo;

int test_parsing(char **av);
long    ft_atoi(char *str);
#endif