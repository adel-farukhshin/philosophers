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

#define TIME_TO_SLEEP 1
#define TIME_TO_THINK 1
#define NB_OF_PHILO 5

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
	usleep(TIME_TO_THINK);
}

void	philosopher(int *nb)
{
	ph_sleep(nb);
	ph_think(nb);
}



int	main()
{
	// struct timeval tv;
	pthread_t *t;
	int	i = 0;

	
	t = malloc(sizeof(pthread_t) * NB_OF_PHILO);
	if (!t)
		return (1);

	while (i < NB_OF_PHILO)
	{
		pthread_create((t + i), NULL, (void *)&philosopher, (t + i));
		printf("Philo %d is created\n", i);
		pthread_detach(t[i]);
		i++;
	}
	i = 0;
	// while (i < NB_OF_PHILO)
	// {
	// 	if (pthread_join(t[i], NULL))
	// 		perror("Failed to join error");
	// 	else
	// 		printf("Philo %d is deleted\n", i);
			
	// 	i++;
	// } // разница между detached и join в том, что в первом случае ресурсы освобождаются сразу по выходу из треда, в то время как, во втором случае необходим вызов join
	
	pthread_exit(0);
	
}
