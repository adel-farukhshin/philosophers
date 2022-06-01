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
	while (!(philo->is_to_die))
	{
		if (i - timestamp() >= time)
			break ;
		usleep(50);
	}
}


void	ph_sleep(t_philo *philo)
{
	// struct timeval tv;

	// gettimeofday(&tv, NULL);
	// tv.tv_sec *= 1000;
	// tv.tv_usec /= 1000;
	// pthread_mutex_lock(philo->out);
	// printf("%lu %d is sleeping\n", tv.tv_sec + tv.tv_usec - 
	// 	philo->start.tv_sec - philo->start.tv_usec, philo->index);
	// pthread_mutex_unlock(philo->out);
	// usleep(philo->to_sleep * 1000);
	print_action(philo, "is sleeping");
	smart_sleep(philo->to_sleep * 1000, philo);
}

void	ph_think(t_philo *philo)
{
	// struct timeval tv;

	// gettimeofday(&tv, NULL);
	// tv.tv_sec *= 1000;
	// tv.tv_usec /= 1000;
	// pthread_mutex_lock(philo->out);
	// printf("%lu %d is thinking\n", tv.tv_sec + tv.tv_usec - 
	// 	philo->start.tv_sec - philo->start.tv_usec, philo->index);	
	// pthread_mutex_unlock(philo->out);
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
	// struct timeval tv;

	// gettimeofday(&tv, NULL);
	// tv.tv_sec *= 1000;
	// tv.tv_usec = tv.tv_usec / 1000;

	pthread_mutex_lock(philo->last_mutex);
	// philo->last.tv_sec = tv.tv_sec;
	// philo->last.tv_usec = tv.tv_usec;
	philo->last = timestamp();
	pthread_mutex_unlock(philo->last_mutex);
	print_action(philo, "is eating");
	// pthread_mutex_lock(philo->out);
	// printf("%lu %d is eating\n", tv.tv_sec + tv.tv_usec - 
	// 	philo->start.tv_sec - philo->start.tv_usec, philo->index);
	// pthread_mutex_unlock(philo->out);
	// usleep(philo->to_eat * 1000);
	smart_sleep(philo->to_eat * 1000, philo);
	

}


void	*philosopher(void *data)
{
	t_philo *philo = data;
	// printf("Philo %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d; right %d, left %d; forks: right - %p, left - %p\n", 
		// philo->index, philo->start.tv_sec, philo->start.tv_usec, philo->to_die, philo->to_eat, philo->to_sleep, 
		// right(philo->index, NB_OF_PHILO), left(philo->index, NB_OF_PHILO), philo->fork_r, philo->fork_l);

	// int	i;

	// struct timeval tv;

	// if (philo->index % 2 == 0)
	// 	usleep(2500);

	// i = 0;
	while (!(*(philo->is_to_die)))
	{ 
		if (*(philo->is_to_die))
			return 0;
		// Take the first fork 
		pthread_mutex_lock(MIN(philo->fork_r, philo->fork_l));
		// gettimeofday(&tv, NULL);
		// tv.tv_sec *= 1000;
		// tv.tv_usec /= 1000;
		// pthread_mutex_lock(philo->out);
		// printf("%lu %d has taken a fork\n", tv.tv_sec + tv.tv_usec - 
		// 	philo->start.tv_sec - philo->start.tv_usec, philo->index);
		// pthread_mutex_unlock(philo->out);
		print_action(philo, "has taken a fork");

		if (*(philo->is_to_die))
		{
			pthread_mutex_unlock(MIN(philo->fork_r, philo->fork_l));
			return 0;
		}
		// Take the second fork 
		pthread_mutex_lock(MAX(philo->fork_r, philo->fork_l));
		// gettimeofday(&tv, NULL);
		// tv.tv_sec *= 1000;
		// tv.tv_usec /= 1000;
		// pthread_mutex_lock(philo->out);
		// printf("%lu %d has taken a fork\n", tv.tv_sec + tv.tv_usec - 
		// 	philo->start.tv_sec - philo->start.tv_usec, philo->index);
		// pthread_mutex_unlock(philo->out);
		print_action(philo, "has taken a fork");

		// if (*(philo->is_to_die))
		// 	return 0;
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
		
		if (*(philo->is_to_die))
			return 0;
		// Think
		ph_think(philo);
		// i++;
	}
	return (0);
}