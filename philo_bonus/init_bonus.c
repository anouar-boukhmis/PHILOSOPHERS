#include "philo_bonus.h"

size_t get_time(void)
{
	struct timeval current;
	size_t timestamp;

	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec)*1000 + (current.tv_usec / 1000);
	return(timestamp);
}

int init_sem(t_semas **sms, int num_philos)
{
	*sms = malloc(sizeof(t_semas));
	if (!(*sms))
		return(-1);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/eat");
	sem_unlink("/dead");
	(*sms)->forks = sem_open("/forks", O_CREAT, 0644, num_philos);
	if ((*sms)->forks == SEM_FAILED)
		return (free(*sms), -1);
	(*sms)->deadlock = sem_open("/dead", O_CREAT, 0644, 1);
	if ((*sms)->deadlock == SEM_FAILED)
		return (free(*sms), sem_close((*sms)->forks), -1);
	(*sms)->eat_lock = sem_open("/eat", O_CREAT, 0644, 1);
	if ((*sms)->eat_lock == SEM_FAILED)
		return (free(*sms), sem_close((*sms)->forks), sem_close((*sms)->deadlock), 1);
	(*sms)->write_lock = sem_open("/write", O_CREAT, 0644, 1);
	if ((*sms)->write_lock == SEM_FAILED)
	{
		free(*sms);
		return (sem_close((*sms)->forks), sem_close((*sms)->deadlock), sem_close((*sms)->eat_lock), -1);
	}
	return (0);
}

t_philo *init_philos(char **av)
{
	int i;
	t_philo *philos;
	t_semas *sms;

	if (init_sem(&sms, ft_atoi1(av[1])) == -1)
		return (NULL);
	philos = (t_philo *)malloc((ft_atoi1(av[1]) * sizeof(t_philo)));
	if (!philos)
		return(NULL);
	i = 0;
	while ( i < ft_atoi1(av[1]))
	{
		philos[i].num_of_philos = ft_atoi1(av[1]);
		philos[i].time_to_die = ft_atoi1(av[2]);
		philos[i].time_to_eat = ft_atoi1(av[3]);
		philos[i].time_to_sleep = ft_atoi1(av[4]);
		philos[i].max_eaten = ft_atoi1(av[5]);
		philos[i].eating = 0;
		philos[i].philo_num = i + 1;
		philos[i].last_meal = get_time();
		philos[i].num_eaten = 0;
		philos[i].sem = sms;
		philos[i].start = get_time();
		philos[i].is_dead = 0;
		i++;
	}
	return(philos);
}
// t_monitor *init_mon(t_philo **philos)
// {
// 	t_monitor	*mon;
// 	int			i;

// 	i = 0;
// 	mon = malloc(sizeof(t_monitor));
// 	if (!mon)
// 		return(NULL);
// 	mon->philos = *philos;
// 	mon->is_dead = 0;
// 	mon->status = -1;
// 	while (i < 200)
// 	{
// 		mon->pids[i] = -1;
// 		i++;
// 	}
// 	return (mon);
// }
