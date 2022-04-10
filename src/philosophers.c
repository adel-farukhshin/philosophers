/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:01:55 by bsarai            #+#    #+#             */
/*   Updated: 2022/03/24 12:01:56 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "philosophers.h"

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
	printf("Philo %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d; right %d, left %d\n", philo->index,
		philo->start.tv_sec, philo->start.tv_usec, philo->to_die, philo->to_eat, philo->to_sleep, 
		right(philo->index, NB_OF_PHILO), left(philo->index, NB_OF_PHILO));


	// ph_sleep(philo->index, philo->to_sleep);
	// ph_think(philo->index);
}

int	init_philos(t_philos *philos, struct timeval tv)
{
	int	i;

	i = 1;
	philos->ph_num = NB_OF_PHILO;
	philos->times_to_eat = T_TO_EAT;
	philos->ph_arr = malloc(sizeof(t_philo) * philos->ph_num);
	if (!philos->ph_arr)
	{
		free(philos);
		return (0);
	}
	while (i <= philos->ph_num)
	{
		philos->ph_arr[i - 1].start.tv_sec = tv.tv_sec;
		philos->ph_arr[i - 1].start.tv_usec = tv.tv_usec;
		philos->ph_arr[i - 1].to_die = TIME_TO_DIE;
		philos->ph_arr[i - 1].to_eat = TIME_TO_EAT;
		philos->ph_arr[i - 1].to_sleep = TIME_TO_SLEEP;
		philos->ph_arr[i - 1].index = i;
		i++;
	}
	return (1);
}



int	main()
{
	t_philos philos;
	struct timeval tv;
	int	i = 0;

	if (gettimeofday(&tv, NULL))
		return (1);
	tv.tv_usec /= 1000;
	if (!init_philos(&philos, tv))
		return (2);
	// printf("sec %ld, ms: %u\n", tv.tv_sec, tv.tv_usec);

	// i = 1;
	// while (i <= philos.ph_num)
	// {
	// 	printf("Phil %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d\n", philos.ph_arr[i - 1].index,
	// 	philos.ph_arr[i - 1].start.tv_sec, philos.ph_arr[i - 1].start.tv_usec, philos.ph_arr[i - 1].to_die, 
	// 	philos.ph_arr[i - 1].to_eat, philos.ph_arr[i - 1].to_sleep);
	// 	i++;
	// }

/*
	pthread_mutex_t *forks;

	forks = malloc(sizeof(pthread_mutex_t) * philos.ph_num);
	if (!forks)
	{
		free(philos.ph_arr);
		return (3);
	}
	i = 0;
	while (i < philos.ph_num)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			while (i)
			{
				i--;
				pthread_mutex_destroy(forks + i);
			}
		}
		i++;
	}

	pthread_t *t;
	t = malloc(sizeof(pthread_t) * philos.ph_num); // может это перенести в philos
	if (!t)
	{
		free(philos.ph_arr);
		return (4);
	}
	i = 0;
	while (i < philos.ph_num)
	{
		if(pthread_create((t + i), NULL, (void *)&philosopher, (philos.ph_arr + i)))
		{
			while (i)
			{
				i--;
				pthread_join(t[i], NULL);
			}
		}
		printf("Philo %d is created\n", philos.ph_arr[i].index);
		// pthread_detach(t[i]);
		i++;
	}
	i = 0;
	while (i < philos.ph_num)
	{
		if (pthread_join(t[i], NULL))
			perror("Failed to join error");
		else
			printf("Philo %d is deleted\n", i);
			
		i++;
	} // разница между detached и join в том, что в первом случае ресурсы освобождаются сразу по выходу из треда, в то время как, во втором случае необходим вызов join
	
	// pthread_exit(0);


	// printf("time at exit: sec %ld, ms %u\n", tv.tv_sec, tv.tv_usec);
	free(t);

	*/
	free(philos.ph_arr);
}
