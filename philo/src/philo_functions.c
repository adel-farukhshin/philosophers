/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:26:58 by bsarai            #+#    #+#             */
/*   Updated: 2022/04/10 15:26:59 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	*min(pthread_mutex_t *r, pthread_mutex_t *l)
{
	if (r < l)
		return (r);
	else
		return (l);
}

pthread_mutex_t	*max(pthread_mutex_t *r, pthread_mutex_t *l)
{
	if (r > l)
		return (r);
	else
		return (l);
}

void	smart_sleep(long long time, t_philo *philo)
{
	long long	i;
	long long	a;

	i = timestamp();
	while (!(philo->data->is_to_die))
	{
		a = timestamp();
		if (a - i >= time)
			break ;
		usleep(50);
	}
}

void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->last_m);
	print_action(philo, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->last_m);
	philo->nb_meal += 1;
	smart_sleep(philo->data->to_eat, philo);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!(philo->is_to_die) && !(philo->data->is_all_ate))
	{
		pthread_mutex_lock(min(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(max(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");
		ph_eat(philo);
		pthread_mutex_unlock(max(philo->fork_r, philo->fork_l));
		pthread_mutex_unlock(min(philo->fork_r, philo->fork_l));
		print_action(philo, "is sleeping");
		smart_sleep(philo->data->to_sleep, philo);
		print_action(philo, "is thinking");
	}
	return (0);
}
