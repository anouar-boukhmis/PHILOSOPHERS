#include "philo_bonus.h"
#include <semaphore.h>

void ft_usleep(int time_ms)
{
    size_t start;
    
    start = get_time();
    while ((get_time() - start) < (size_t)time_ms)
        usleep(333);
}


void print_message(t_philo *philo, char *message)
{
    size_t  timestamp;

    sem_wait(philo->sem->write_lock);
    timestamp = get_time() - philo->start;
    printf("%zu %d %s\n", timestamp, philo->philo_num, message);
    sem_post(philo->sem->write_lock);
}

void philo_is_think(t_philo *philo)
{
    print_message(philo, "is thinking");
}

void philo_is_sleep(t_philo *philo)
{
    print_message(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep);
}


void philo_is_eating(t_philo *philo)
{
    sem_wait(philo->sem->forks);
	print_message(philo,"has taken a fork");
    if (philo->num_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        sem_post(philo->sem->forks);
        return ;
    }
    sem_wait(philo->sem->forks);
	print_message(philo,"has taken a fork");
	philo->eating = 1;
	print_message( philo, "is eating");
	sem_wait(philo->sem->eat_lock);
	philo->last_meal = get_time();
	philo->num_eaten++;
	sem_post(philo->sem->eat_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	sem_post(philo->sem->forks);
    sem_post(philo->sem->forks);
}