/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:01:01 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/05 13:01:03 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

static void		create_processes(t_philos *philos, pid_t *pids);
static int		kill_processes(pid_t *pids, int nb);
static void		wait_processes(t_philos *philos, pid_t *pids);

int	launch(t_philos *philos)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * philos->ph_num);
	if (!pids)
	{
		sem_delete(&(philos->philo), 2);
		return (1);
	}
	philos->philo.start = timestamp();
	create_processes(philos, pids);
	wait_processes(philos, pids);
	free(pids);
	return (0);
}

static void	create_processes(t_philos *philos, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < philos->ph_num)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			kill_processes(pids, i - 1);
			return ;
		}
		if (pids[i] == 0)
		{
			philos->philo.index = i + 1;
			philos->philo.last_meal = timestamp();
			philosopher(&(philos->philo));
		}
		i++;
	}
}

static int	kill_processes(pid_t *pids, int nb)
{
	while (nb > -1)
	{
		kill(pids[nb], SIGKILL);
		nb--;
	}
	return (0);
}

static void	wait_processes(t_philos *philos, pid_t *pids)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			kill_processes(pids, philos->ph_num - 1);
			break ;
		}
	}
}
