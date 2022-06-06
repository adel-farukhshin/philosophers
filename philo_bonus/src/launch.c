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

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

/*

int	is_all_ate(t_philos *philos)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (philos->times_to_eat != -1 && i < philos->ph_num)
	{
		if (((philos->ph_arr) + i)->nb_meal >= philos->times_to_eat)
			nb++;
		i++;
	}
	if (nb == philos->ph_num)
	{
		philos->data.is_all_ate = 1;
		return (1);
	}
	return (0);
}

int	is_died(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->ph_num
		&& !(philos->data.is_to_die) && !(philos->data.is_all_ate))
	{
		pthread_mutex_lock(((philos->ph_arr) + i)->last_m);
		if (timedif(philos->ph_arr[i].last_meal
				, timestamp()) >= philos->data.to_die)
		{
			pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
			print_action(philos->ph_arr + i, "died");
			philos->data.is_to_die = 1;
			return (1);
		}
		pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
		if (is_all_ate(philos))
			return (2);
		i++;
	}
	return (0);
}

int	thread_delete(pthread_t *t, int nb)
{
	int	error;

	error = 0;
	while (nb > -1)
	{
		if (pthread_join(t[nb], NULL))
			error = 2;
		nb--;
	}
	return (error);
}

*/

// int	thread_create(t_philos *philos, pthread_t	*t)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos->ph_num)
// 	{
// 		if (pthread_create((t + i)
// 				, NULL, philosopher, (philos->ph_arr + i)))
// 		{
// 			if (thread_delete(t, i - 1))
// 				return (1);
// 		}
// 		(philos->ph_arr + i)->last_meal = timestamp();
// 		i++;
// 	}
// 	return (0);
// }

// int	launch(t_philos *philos)
// {	
// 	pthread_t	*t;
// 	int			i;
// 	int			error;

// 	t = malloc(sizeof(pthread_t) * philos->ph_num);
// 	if (!t)
// 		return (1);
// 	i = 0;
// 	philos->data.start = timestamp();
// 	if (thread_create(philos, t))
// 	{
// 		free (t);
// 		return (2);
// 	}
// 	while (1)
// 		if (is_died(philos))
// 			break ;
// 	error = thread_delete(t, philos->ph_num - 1);
// 	free(t);
// 	return (error);
// }

int	kill_processes(pid_t *pids, int nb)
{
	// int	i;

	// i = 0;
	// while (i < nb)
	while (nb >= -1)
	{
		kill(pids[nb], SIGKILL);
		nb--;
		// i++;
	}
	return (0);
}

int	launch(t_philos *philos)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * philos->ph_num);
	if (!pids)
		return (1);
	philos->philo.start = timestamp();
	int	i = 0;
	while (i < philos->ph_num)
	{
		pids[i] = fork();
		// printf("pid %d\n", pids[i]);
		if (pids[i] == -1)
			kill_processes(pids, i - 1);
		if (pids[i] == 0)
		{
			// printf("proc created\n");
			philos->philo.index = i + 1;
			philos->philo.last_meal = timestamp();
			philosopher(&(philos->philo));
		}
		// usleep(25000);
		i++;
	}
	int	signal;
	while (waitpid(-1, &signal, 0) > 0) // or > 0
	{
		if (WEXITSTATUS(signal) == 1)
			return (kill_processes(pids, philos->ph_num - 1));
	}
		
	free(pids);
	return (0);
}