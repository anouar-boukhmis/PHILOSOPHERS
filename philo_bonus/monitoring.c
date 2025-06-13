#include "philo_bonus.h"
#include <semaphore.h>




int check_died(t_philo *philos)
{
    int died = 0;
    
    sem_wait(philos->sem->eat_lock);
    if (get_time() - philos->last_meal >= (size_t)philos->time_to_die && philos->eating == 0)
        died = 1;
    sem_post(philos->sem->eat_lock);
    
    return died;
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
        sem_wait(philos[i].sem->eat_lock);
        if(philos[i].num_eaten < philos[0].max_eaten)
            all_ate_enough = 0;  
        sem_post(philos[i].sem->eat_lock);
        i++;
    }
    if(all_ate_enough)
    {
        print_message(philos, "died");
        exit(33);
    }
    return(0);
}
