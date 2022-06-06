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
#include <stdlib.h>

/*

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

*/

// void	*philosopher(void *data)
// {
// 	t_philo	*philo;

// 	philo = data;
// 	if (philo->index % 2 == 0)
// 		usleep(20);
// 	if (philo->data->ph_num == 1)
// 	{
// 		smart_sleep(philo->data->to_die, philo);
// 		philo->data->is_to_die = 1;
// 	}
// 	while (!(philo->data->is_to_die) && !(philo->data->is_all_ate))
// 	{
// 		pthread_mutex_lock(min(philo->fork_r, philo->fork_l));
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(max(philo->fork_r, philo->fork_l));
// 		print_action(philo, "has taken a fork");
// 		ph_eat(philo);
// 		pthread_mutex_unlock(max(philo->fork_r, philo->fork_l));
// 		pthread_mutex_unlock(min(philo->fork_r, philo->fork_l));
// 		print_action(philo, "is sleeping");
// 		smart_sleep(philo->data->to_sleep, philo);
// 		print_action(philo, "is thinking");
// 	}
// 	return (0);
// }


void	*to_stop(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		// Check times of eating

		// Check is died
		if (timestamp() - philo->start >= philo->to_die)
		{
			philo->is_to_die = 1;
			sem_wait(philo->out);
			printf("%llu %d is_died\n", timestamp() - philo->start, philo->index);
			sem_post(philo->out);
			// print is died
			break ;
		}
		
	}


	// Maybe put it in cycle?
	if (philo->is_to_die)
		exit (1);
	else
		exit (0);
}


int	philosopher(t_philo *philo)
{
	pthread_t	t;
	

	if (pthread_create(&t, NULL, to_stop, philo))
		return (1);
	
	while (!philo->is_to_die)
	// routine
	{

	}
	
	
	if (pthread_join(t, NULL))
	{
		printf("a\n");
		return (1);
	}
	else
	{
		printf("b\n");
		return (0);
	}
}