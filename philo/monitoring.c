#include "philo.h"

int check_died(t_philo *philos)
{
    pthread_mutex_lock(philos->meal_lock);
    if (get_time() - philos->last_meal > (size_t)philos->time_to_die && philos->eating == 0)
    {
        pthread_mutex_unlock(philos->meal_lock);
        return(1);
    }
    pthread_mutex_unlock(philos->meal_lock);
    return(0);
}

int check_all_philos_eat(t_philo *philos)
{
    int i;
    int all_ate_enough = 1;
    
    if (philos[0].num_to_eat == -1)
        return(0);
        
    i = 0;
    while(i < philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[i].meal_lock);
        if(philos[i].meals_eaten < philos[0].num_to_eat)
            all_ate_enough = 0;  
        pthread_mutex_unlock(philos[i].meal_lock);
        i++;
    }
    if(all_ate_enough)
    {
        pthread_mutex_lock(philos[0].dead_lock);
        *(philos[0].dead) = 1;
        pthread_mutex_unlock(philos[0].dead_lock);
        return(1);
    }
    return(0);
}

int set_to_finish(t_philo *philo)
{

    int i;

    i = 0;
    while (i < philo[0].num_of_philos)
    {
        if (check_died(&philo[i])== 1)
        {
            print_message(&philo[i], "died");
            pthread_mutex_lock(philo[0].dead_lock);
            *(philo[i].dead) = 1;
            pthread_mutex_unlock(philo[0].dead_lock);
            return(1);
        }
        i++;
    }
    return(0);
}

void *check_diedloop(void *ptr)
{
    t_monitor *monitor;
    monitor = (t_monitor *)ptr;
    while (1)
    {
        if(set_to_finish(monitor->philos) == 1 || check_all_philos_eat(monitor->philos))
            break;
    }
    return(monitor->philos);
}
