/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:50:57 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/06/22 16:03:38 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	kill_all_processes(t_philo *philos, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue ;
}

static int	handle_process_exit(int status, t_philo *philos, pid_t *pids)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			kill_all_processes(philos, pids);
			return (1);
		}
		else if (WEXITSTATUS(status) == 0)
			return (2);
	}
	return (0);
}

static int	wait_for_completion(t_philo *philos, pid_t *pids)
{
	int		status;
	int		finished_count;
	int		result;
	pid_t	finished_pid;

	finished_count = 0;
	while (finished_count < philos->num_of_philos)
	{
		finished_pid = waitpid(-1, &status, 0);
		if (finished_pid > 0)
		{
			result = handle_process_exit(status, philos, pids);
			if (result == 1)
				return (1);
			else if (result == 2)
				finished_count++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	pid_t	*pids;
	int		result;

	if (test_parsing(av, ac) == -1)
		return (1);
	philos = init_philos(av);
	if (!philos)
		return (1);
	pids = malloc(sizeof(pid_t) * philos->num_of_philos);
	if (!pids)
	{
		cleanup_semaphores(philos->sem);
		free(philos);
		return (1);
	}
	create_processes(philos, pids);
	result = wait_for_completion(philos, pids);
	free(pids);
	cleanup_semaphores(philos->sem);
	free(philos);
	return (result);
}
