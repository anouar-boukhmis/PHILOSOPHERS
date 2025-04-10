#include "philo.h"

void print_message(t_philo *philo, char *message)
{
    size_t  timestamp;
    if (check_died1(philo))
        return;
    timestamp = get_time() - philo->start;
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d %s\n", timestamp, philo->num, message);
    pthread_mutex_unlock(philo->write_lock);
}
void philo_is_think(t_philo *philo)
{
    if (check_died1(philo) == 1)
        return;
    print_message(philo, "is thinking");
}

void ft_usleep(int time_ms)
{
    size_t start;
    
    start = get_time();
    while ((get_time() - start) < (size_t)time_ms)
        usleep(200);
}

void philo_is_sleep(t_philo *philo)
{
    if (check_died1(philo) == 1)
        return;
    print_message(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep);
}

void philo_is_eating(t_philo *philo)
{
    if (check_died1(philo) == 1)
        return;
    pthread_mutex_lock(philo->rfork);
    print_message(philo, "has taken a fork");
    if (philo->num_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->rfork);
        return;
    }
    if (check_died1(philo) == 1)
    {
        pthread_mutex_unlock(philo->rfork);
        return;
    }
    pthread_mutex_lock(philo->lfork);
    print_message(philo, "has taken a fork");
    if (check_died1(philo) == 1)
    {
        pthread_mutex_unlock(philo->lfork);
        pthread_mutex_unlock(philo->rfork);
        return;
    }
    philo->eating = 1;
    print_message(philo, "is eating");
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_eat);
    philo->eating = 0;
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    if (check_died1(philo) == 1)
        return;
}


