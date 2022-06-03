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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



void		smart_sleep(long long time, t_philo *philo)
{
	long long i;
	
	i = timestamp();
	while (!(philo->data->is_to_die))
	{
		if (i - timestamp() >= time)
			break ;
		usleep(50);
	}
}


void	ph_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->to_sleep * 1000, philo);
}

void	ph_think(t_philo *philo)
{
	print_action(philo, "is thinking");
}


int right(int n, int ph_num)
{
	int	res;

	res = (n - 1) % ph_num;
	if (res == 0)
		res = ph_num;
	return (res);
}

int	left(int n, int ph_num)
{
	int	res;

	res = (n + 1) % ph_num;
	if (res == 0)
		res = ph_num;
	return (res);
}

void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->last_m);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->last_m);
	print_action(philo, "is eating");
	smart_sleep(philo->data->to_eat * 1000, philo);

}


void	*philosopher(void *data)
{
	t_philo *philo = data;

	// if (philo->index % 2 == 0)
	// 	usleep(2500);

	// i = 0;
	while (!(philo->data->is_to_die))
	{ 
		// Take the first fork 
		pthread_mutex_lock(MIN(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");

		// Take the second fork 
		pthread_mutex_lock(MAX(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");

		// Eating
		ph_eat(philo);
		pthread_mutex_unlock(MAX(philo->fork_r, philo->fork_l));
		pthread_mutex_unlock(MIN(philo->fork_r, philo->fork_l));

		// Sleep
		ph_sleep(philo);

		// Think
		ph_think(philo);
	}
	return (0);
}