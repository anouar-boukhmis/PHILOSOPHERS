#include "philo.h"




int main(int ac, char **av)
{
    t_monitor       monitor;
    pthread_mutex_t *forks;
    t_philo         *philos;

    test_parsing(av, ac);
    forks = (pthread_mutex_t *)malloc(ft_atoi(av[1])*sizeof(pthread_mutex_t));
    philos = (t_philo *)malloc(ft_atoi(av[1])*sizeof(t_philo));
    init_monitor(&monitor, philos);
    init_forks(forks, ft_atoi(av[1]));
    init_philos(philos, av, forks, &monitor);
    creat_threads(&monitor, forks);
    free(forks);
    free(philos);
    return(0);
}
