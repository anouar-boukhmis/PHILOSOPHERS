#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_semas
{
	sem_t *write_lock;
	sem_t *eat_lock;
	sem_t *deadlock;
	sem_t *forks;
}t_semas;

typedef struct s_philo
{
	int philo_num;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int num_of_philos;
	size_t last_meal;
	int eating;
	int num_eaten;
	int max_eaten;
	int is_dead;
	size_t	start;
	t_semas *sem;

}t_philo;


typedef struct s_monitor
{
	t_philo	*philos;
	int		status;
	int		is_dead;
	int		pids[200];
}t_monitor;

long		ft_atoi(char *str);
int			test_parsing(char **av, int ac);
t_philo		*init_philos(char **av);
t_monitor	*init_mon(t_philo **philos, char **av);
size_t		get_time(void);








#endif