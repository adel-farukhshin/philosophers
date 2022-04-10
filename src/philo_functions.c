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

void	ph_sleep(int nb, int to_sleep)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	printf("%u %d is sleeping\n", tv.tv_usec, nb);
	sleep(to_sleep);
}

void	ph_think(int nb)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%u %d is thinking\n", tv.tv_usec, nb);
	// usleep(TIME_TO_THINK);
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


void	philosopher(t_philo *philo)
{
	printf("Philo %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d; right %d, left %d; forks: right - %p, left - %p\n", 
		philo->index, philo->start.tv_sec, philo->start.tv_usec, philo->to_die, philo->to_eat, philo->to_sleep, 
		right(philo->index, NB_OF_PHILO), left(philo->index, NB_OF_PHILO), philo->fork_r, philo->fork_l);


	// ph_sleep(philo->index, philo->to_sleep);
	// ph_think(philo->index);
}