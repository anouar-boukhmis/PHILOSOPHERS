#include "philo.h"

int	check_died1(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead== 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void    *philo_routine(void *ptr)
{
    t_philo *philo;
    philo = (t_philo *)ptr;
    if(philo->num % 2 == 0)
        usleep(100);
    while(check_died1(philo) == 0)
    {
        philo_is_eating(philo);
        philo_is_sleep(philo);
        philo_is_think(philo);
    }
    return (ptr);
}

void creat_threads(t_monitor *monitor, pthread_mutex_t *forks)
{
    pthread_t mon;
    int i;

    i = 0;
    if (pthread_create(&mon, NULL, &check_diedloop, monitor) != 0)
        ccclean(forks, monitor->philos);
    while(i < monitor->philos[0].num_of_philos)
    {
        if (pthread_create(&monitor->philos[i].thread, NULL, &philo_routine, &monitor->philos[i]) != 0)
            ccclean(forks, monitor->philos);
        i++;
    }
    if(pthread_join(mon, NULL) != 0)
        ccclean(forks, monitor->philos);
    i = 0;
    while(i < monitor->philos[0].num_of_philos)
    {
        if (pthread_join(monitor->philos[i].thread, NULL) != 0)
            ccclean(forks, monitor->philos);
        i++;
    }
}