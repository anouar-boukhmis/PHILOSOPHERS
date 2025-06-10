#include "philo_bonus.h"
#include <semaphore.h>




int check_died(t_philo *philos)
{
    sem_wait(philos->sem->eat_lock);
    if (get_time() - philos->last_meal >= (size_t)philos->time_to_die && philos->eating == 0)
    {
        sem_post(philos->sem->eat_lock);
        return(1);
    }
    sem_post(philos->sem->eat_lock);
    return(0);
}


int check_all_philos_eat(t_philo *philos)
{
    int i;
    int all_ate_enough = 1;
    
    if (philos[0].max_eaten == -1)
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