#include "philo_bonus.h"
#include <semaphore.h>


void do_your_work(t_monitor *mon)
{
	
}
int main(int ac, char **av)
{
	t_philo		*philos;
	t_monitor	*mon;
	int			i;

	philos = init_philos(av);
	mon = init_mon(&philos, av);
	while (i < philos->num_of_philos)
	{
		mon->pids[i] = fork();
		if (mon->pids[i] == 0)
			do_your_work(mon);
		i++;
	}
}