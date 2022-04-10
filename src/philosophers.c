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

#define TIME_TO_DIE 10
#define TIME_TO_SLEEP 1
#define	TIME_TO_EAT 1
// #define TIME_TO_THINK 1
#define NB_OF_PHILO 5
#define T_TO_EAT -1

void	ph_sleep(int *nb)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	printf("%u %d is sleeping\n", tv.tv_usec, *nb);
	sleep(TIME_TO_SLEEP);
}

void	ph_think(int *nb)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%u %d is thinking\n", tv.tv_usec, *nb);
	// usleep(TIME_TO_THINK);
}

void	philosopher(int *nb)
{
	ph_sleep(nb);
	ph_think(nb);
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
	// pthread_t *t;
	t = malloc(sizeof(pthread_t) * NB_OF_PHILO); // может это перенести в philos
	if (!t)
		return (1);

	while (i < NB_OF_PHILO)
	{
		pthread_create((t + i), NULL, (void *)&philosopher, (t + i));
		printf("Philo %d is created\n", i);
		// pthread_detach(t[i]);
		i++;
	}
	i = 0;
	while (i < NB_OF_PHILO)
	{
		if (pthread_join(t[i], NULL))
			perror("Failed to join error");
		else
			printf("Philo %d is deleted\n", i);
			
		i++;
	} // разница между detached и join в том, что в первом случае ресурсы освобождаются сразу по выходу из треда, в то время как, во втором случае необходим вызов join
	
	// pthread_exit(0);

*/
	// printf("time at exit: sec %ld, ms %u\n", tv.tv_sec, tv.tv_usec);
	free(philos.ph_arr);
}
