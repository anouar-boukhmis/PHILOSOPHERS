/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:50:57 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/14 18:02:11 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_semaphores(t_semas *sem)
{
	if (sem)
	{
		if (sem->forks != SEM_FAILED)
		{
			sem_close(sem->forks);
			sem_unlink("/forks");
		}
		if (sem->write_lock != SEM_FAILED)
		{
			sem_close(sem->write_lock);
			sem_unlink("/write");
		}
		if (sem->eat_lock != SEM_FAILED)
		{
			sem_close(sem->eat_lock);
			sem_unlink("/eat");
		}
		if (sem->deadlock != SEM_FAILED)
		{
			sem_close(sem->deadlock);
			sem_unlink("/dead");
		}
		free (sem);
	}
}

void	handle_died(t_philo *philo)
{
	sem_wait(philo->sem->write_lock);
	printf("%zu %d died\n", get_time() - philo->start, philo->philo_num);
	exit(33);
}

static void	handle_death_cleanup(t_philo *philos, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
	sem_post(philos->sem->deadlock);
}

static void	create_processes(t_philo *philos, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			do_your_work(&philos[i]);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	pid_t	*pids;
	int		status;

	if (test_parsing(av, ac) == -1)
		return (1);
	philos = init_philos(av);
	pids = malloc(sizeof(pid_t) * philos->num_of_philos);
	create_processes(philos, pids);
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 33)
		handle_death_cleanup(philos, pids);
	free(pids);
	cleanup_semaphores(philos->sem);
	free(philos);
	return (0);
}
