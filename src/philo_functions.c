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



void	ph_sleep(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tv.tv_sec *= 1000;
	tv.tv_usec /= 1000;
	printf("%lu %d is sleeping\n", tv.tv_sec + tv.tv_usec - 
		philo->start.tv_sec - philo->start.tv_usec, philo->index);
	usleep(philo->to_sleep * 1000);
}

void	ph_think(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tv.tv_sec *= 1000;
	tv.tv_usec /= 1000;
	printf("%lu %d is thinking\n", tv.tv_sec + tv.tv_usec - 
		philo->start.tv_sec - philo->start.tv_usec, philo->index);	
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
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tv.tv_sec *= 1000;
	tv.tv_usec = tv.tv_usec / 1000;

	philo->last.tv_sec = tv.tv_sec;
	philo->last.tv_usec = tv.tv_usec;
	printf("%lu %d is eating\n", tv.tv_sec + tv.tv_usec - 
		philo->start.tv_sec - philo->start.tv_usec, philo->index);
	usleep(philo->to_eat * 1000);
	

}


void	*philosopher(void *data)
{
	t_philo *philo = data;
	// printf("Philo %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d; right %d, left %d; forks: right - %p, left - %p\n", 
		// philo->index, philo->start.tv_sec, philo->start.tv_usec, philo->to_die, philo->to_eat, philo->to_sleep, 
		// right(philo->index, NB_OF_PHILO), left(philo->index, NB_OF_PHILO), philo->fork_r, philo->fork_l);

	// int	i;

	struct timeval tv;

	gettimeofday(&tv, NULL);

	// i = 0;
	while (1)
	{ 
		if (*(philo->is_to_die))
		{
			// printf("%d %u %d return\n", *(philo->is_to_die), tv.tv_usec, philo->index);
			return 0;
		}
		// Take the first fork 
		pthread_mutex_lock(MIN(philo->fork_r, philo->fork_l));
		gettimeofday(&tv, NULL);
		tv.tv_sec *= 1000;
		tv.tv_usec /= 1000;
		printf("%lu %d has taken a fork\n", tv.tv_sec + tv.tv_usec - 
			philo->start.tv_sec - philo->start.tv_usec, philo->index);
		
		// Take the second fork 
		pthread_mutex_lock(MAX(philo->fork_r, philo->fork_l));
		gettimeofday(&tv, NULL);
		tv.tv_sec *= 1000;
		tv.tv_usec /= 1000;
		printf("%lu %d has taken a fork\n", tv.tv_sec + tv.tv_usec - 
			philo->start.tv_sec - philo->start.tv_usec, philo->index);

		// Eating
		ph_eat(philo);


		pthread_mutex_unlock(MAX(philo->fork_r, philo->fork_l));
		pthread_mutex_unlock(MIN(philo->fork_r, philo->fork_l));
		
		// usleep(philo->to_sleep * 1000);
		if (*(philo->is_to_die))
			return 0;
		
		// Sleep
		ph_sleep(philo);
		if (*(philo->is_to_die))
			return 0;
		
		// Think
		ph_think(philo);
		// i++;
	}
}