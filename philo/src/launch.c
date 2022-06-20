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
static int	to_stop(t_philos *philos);
static int	is_to_die(t_philo *philo);
static int	is_all_ate(t_philos *philos);

int	launch(t_philos *philos)
{	
	pthread_t	*t;

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
	free(t);
	return (0);
}

static int	thread_create(t_philos *philos, pthread_t *t)
{
	int	i;

	i = 0;
	while (i < philos->ph_num)
	{
		(philos->ph_arr + i)->last_meal = timestamp();
		if (pthread_create((t + i)
				, NULL, philosopher, (philos->ph_arr + i)))
		{
			return (1);
		}
		pthread_detach(*(t + i));
		usleep(100);
		i++;
	}
	return (0);
}

static int	to_stop(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->ph_num)
	{
		if (is_to_die(philos->ph_arr + i))
			return (1);
		if (is_all_ate(philos))
			return (2);
		i++;
	}
	return (0);
}

static int	is_to_die(t_philo *philo)
{
	pthread_mutex_lock(philo->last_m);
	if (timedif(philo->last_meal
			, timestamp()) >= philo->data->to_die)
	{
		pthread_mutex_unlock(philo->last_m);
		print_action(philo, "died");
		philo->is_to_die = 1;
		pthread_mutex_lock(philo->data->out_m);
		return (1);
	}
	pthread_mutex_unlock(philo->last_m);
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
