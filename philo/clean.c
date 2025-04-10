#include "philo.h"



void ccclean(pthread_mutex_t *forks, t_philo *philos)
{
    int i;

    i = 0;
    pthread_mutex_destroy(philos->write_lock);
    pthread_mutex_destroy(philos->dead_lock);
    pthread_mutex_destroy(philos->meal_lock);
    while (i < philos->num_of_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    printf("Error in Thread\n");
}