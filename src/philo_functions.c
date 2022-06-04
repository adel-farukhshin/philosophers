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
	long long a;
	
	i = timestamp();
	// print_action(philo, "a ts");
	while (!(philo->data->is_to_die))
	{
		a = timestamp();
		if (a - i >= time)
			break ;
		usleep(50);
		// print_action(philo, "ss: cycle");
		// printf("n %llu st %llu min %llu t %llu\n", a, i, a - i, time);
	}
	// print_action(philo, "ss: at the end ");
}


void	ph_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->to_sleep, philo);
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
	print_action(philo, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->last_m);
	// print_action(philo, "a l_m");
	smart_sleep(philo->data->to_eat, philo);
	// print_action(philo, "a ss");
}


void	*philosopher(void *data)
{
	t_philo *philo = data;

	if (philo->index % 2 == 0)
		usleep(2500);

	if (philo->data->ph_num == 1)
	{
		smart_sleep(philo->data->to_die, philo);
		philo->data->is_to_die = 1;
	}

	// i = 0;
	while (!(philo->data->is_to_die))
	{ 
		// Take the first fork 
		pthread_mutex_lock(MIN(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");

		// Take the second fork 
		pthread_mutex_lock(MAX(philo->fork_r, philo->fork_l));
		print_action(philo, "has taken a fork");

		// print_action(philo, "aaaa");
		// Eating
		ph_eat(philo);
		// print_action(philo, "ab");
		pthread_mutex_unlock(MAX(philo->fork_r, philo->fork_l)); 
		// print_action(philo, "ac");
		pthread_mutex_unlock(MIN(philo->fork_r, philo->fork_l));
		
		// print_action(philo, "bbb");

		// Sleep
		ph_sleep(philo);

		// print_action(philo, "cc");
		// Think
		ph_think(philo);
		// print_action(philo, "ddd");
	}
	return (0);
}