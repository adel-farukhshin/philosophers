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

static int	thread_create(t_philos *philos, pthread_t *t);
static int	thread_delete(pthread_t *t, int nb);
static int	to_stop(t_philos *philos);
static int	is_all_ate(t_philos *philos);

int	launch(t_philos *philos)
{	
	pthread_t	*t;
	int			error;

	t = malloc(sizeof(pthread_t) * philos->ph_num);
	if (!t)
		return (1);
	philos->data.start = timestamp();
	if (thread_create(philos, t))
	{
		free (t);
		return (2);
	}
	while (1)
		if (to_stop(philos))
			break ;
	error = thread_delete(t, philos->ph_num - 1);
	free(t);
	return (error);
}

static int	thread_create(t_philos *philos, pthread_t *t)
{
	int	i;

	i = 0;
	while (i < philos->ph_num)
	{
		if (pthread_create((t + i)
				, NULL, philosopher, (philos->ph_arr + i)))
		{
			if (thread_delete(t, i - 1))
				return (1);
		}
		(philos->ph_arr + i)->last_meal = timestamp();
		i++;
	}
	return (0);
}

static int	thread_delete(pthread_t *t, int nb)
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

static int	to_stop(t_philos *philos)
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

static int	is_all_ate(t_philos *philos)
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
