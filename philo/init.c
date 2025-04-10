#include "philo.h"

void init_monitor(t_monitor *t, t_philo *philos)
{
    t->dead_flag = 0;
    t->philos = philos;
    pthread_mutex_init(&(t->dead_lock), NULL);
    pthread_mutex_init(&(t->meal_lock), NULL);
    pthread_mutex_init(&(t->write_lock), NULL);
}

void init_forks(pthread_mutex_t *forks, int num)
{
    int i;

    i = 0;
    while (i < num)
    {
       if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            printf("Error initializing fork mutex\n");
            return;
        }
        i++;
    }
}
size_t get_time(void)
{
    struct timeval current;
    size_t timestamp;

    gettimeofday(&current, NULL);
    timestamp = (current.tv_sec)*1000 + (current.tv_usec / 1000);
    return(timestamp);
}
void init_philos(t_philo *philo, char **argv, pthread_mutex_t *forks, t_monitor *monitor)
{
    int i;
    i = 0;
    monitor->dead_flag = 0;
    while( i < ft_atoi(argv[1]))
    {
        philo[i].num = i +1;
        philo[i].eating = 0;
        philo[i].meals_eaten = 0;
        philo[i].num_of_philos = ft_atoi(argv[1]);
        philo[i].time_to_die = ft_atoi(argv[2]);
        philo[i].time_to_eat = ft_atoi(argv[3]);
        philo[i].time_to_sleep = ft_atoi(argv[4]);
        philo[i].dead_lock = &(monitor->dead_lock);
        philo[i].write_lock = &(monitor->write_lock);
        philo[i].meal_lock = &(monitor->meal_lock);
        philo[i].start = get_time();
        philo[i].last_meal = get_time();
        philo[i].dead = &monitor->dead_flag;
        if(argv[5])
            philo[i].num_to_eat = ft_atoi(argv[5]);
        else
            philo[i].num_to_eat = -1;
        philo[i].lfork = &forks[i];
        if (i == 0)
            philo[i].rfork = &forks[philo[i].num_of_philos -1];
        else
            philo[i].rfork = &forks[i -1];
        i++;
    }
}
