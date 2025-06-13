#include "philo.h"

void print_message(t_philo *philo, char *message)
{
    size_t  timestamp;

    pthread_mutex_lock(philo->write_lock);
    if (!philo->dead ||  check_died1(philo))
    {
        pthread_mutex_unlock(philo->write_lock);
        return;
    }
    timestamp = get_time() - philo->start;
    printf("%zu %d %s\n", timestamp, philo->num, message);
    pthread_mutex_unlock(philo->write_lock);
}
void philo_is_think(t_philo *philo)
{
    if (check_died1(philo))
        return ;
    print_message(philo, "is thinking");
}

void ft_usleep(int time_ms, t_philo *philo)
{
    size_t start;
    
    start = get_time();
    while ((get_time() - start) < (size_t)time_ms && !check_died1(philo))
        usleep(333);
}

void philo_is_sleep(t_philo *philo)
{
    if (check_died1(philo))
        return ;
    print_message(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep, philo);
}

void philo_is_eating(t_philo *philo)
{
    if (check_died1(philo))
        return ;
    if (philo->num % 2 != 0)
    {
        pthread_mutex_lock(philo->lfork);
	    print_message(philo,"has taken a fork");
        if (philo->num_of_philos == 1)
        {
            ft_usleep(philo->time_to_die, philo);
            pthread_mutex_unlock(philo->lfork);
            return ;
        }
	    pthread_mutex_lock(philo->rfork);
	    print_message( philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->rfork);
	    print_message(philo,"has taken a fork");
        pthread_mutex_lock(philo->lfork);
	    print_message(philo,"has taken a fork");
    }
	philo->eating = 1;
	print_message( philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}


