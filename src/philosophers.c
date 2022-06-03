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
// #include <sys/time.h>
#include <unistd.h>
// #include <pthread.h>
#include <stdlib.h>

#include "philosophers.h"

// int	init_philos(t_philos *philos)
// {
// 	int	i;

// 	i = 1;
// 	philos->ph_num = NB_OF_PHILO;
// 	philos->times_to_eat = T_TO_EAT;
// 	philos->is_to_die = 0;
// 	philos->ph_arr = malloc(sizeof(t_philo) * philos->ph_num);
// 	if (!philos->ph_arr)
// 	{
// 		free(philos);
// 		return (0);
// 	}
// 	while (i <= philos->ph_num)
// 	{
// 		philos->ph_arr[i - 1].start = timestamp();
// 		// philos->ph_arr[i - 1].last.tv_sec = tv.tv_sec;
// 		// philos->ph_arr[i - 1].last.tv_usec = tv.tv_usec;
// 		philos->ph_arr[i - 1].to_die = TIME_TO_DIE;
// 		philos->ph_arr[i - 1].to_eat = TIME_TO_EAT;
// 		philos->ph_arr[i - 1].to_sleep = TIME_TO_SLEEP;
// 		philos->ph_arr[i - 1].index = i;
// 		philos->ph_arr[i - 1].is_to_die = &philos->is_to_die;
// 		i++;
// 	}
// 	return (1);
// }

// void	forks_delete(pthread_mutex_t *forks, int nb)
// {
// 	while (nb > -1)
// 	{
// 		pthread_mutex_destroy(forks + nb);
// 		nb--;
// 	}
// }

// pthread_mutex_t *forks_init(t_philos *philos)
// {
// 	pthread_mutex_t *forks;
// 	int				i;

// 	i = 0;
// 	forks = malloc(sizeof(pthread_mutex_t) * philos->ph_num);
// 	if (!forks)
// 	{
// 		free(philos->ph_arr);
// 		return (NULL);	
// 	}
// 	while (i < philos->ph_num)
// 	{
// 		if (pthread_mutex_init(forks + i, NULL))
// 		{
// 			forks_delete(forks, i - 1);
// 			free(philos->ph_arr);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (forks);
// }

// void	forks_to_philos(t_philos *philos, pthread_mutex_t *forks)
// {
// 	int	i;

// 	i = 1;
// 	while (i <= philos->ph_num)
// 	{
// 		philos->ph_arr[i - 1].fork_l = forks + i - 1;
// 		if (i == 1)
// 			philos->ph_arr[i - 1].fork_r = forks + philos->ph_num - 1;
// 		else
// 			philos->ph_arr[i - 1].fork_r = forks + i - 2;
// 		// printf("philo %d r %p, l %p\n", philos->ph_arr[i - 1].index, philos->ph_arr[i - 1].fork_r, 
// 		// 		philos->ph_arr[i - 1].fork_l);
// 		i++;
// 	}
// }

// unsigned long delta(struct timeval start, struct timeval end)
// {
// 	unsigned long	secs;
// 	unsigned int	usecs;

// 	secs = (end.tv_sec - start.tv_sec) * 1000;
// 	// printf("secs: %ld, end %ld, start %ld\n", secs, end.tv_sec, start.tv_sec);
// 	usecs = end.tv_usec - start.tv_usec;
// 	// printf("usecs: %u, end %u, start %u\n", usecs, end.tv_usec, start.tv_usec);
// 	secs += (unsigned long) usecs;
// 	// printf("secs: %ld\n", secs);
// 	return (secs);
// }





int	main()
{
	t_philos philos;
	int	i = 0;

	// Initialize
	if (initialize(&philos))
		return (1);

	if (launch(&philos))
		return (2);


	// Threads Initialization
	// pthread_t *t;
	// t = malloc(sizeof(pthread_t) * philos.ph_num); // может это перенести в philos
	// if (!t)
	// {
	// 	forks_delete(forks, philos.ph_num - 1);
	// 	free(forks);
	// 	free(philos.ph_arr);
	// 	pthread_mutex_destroy(&out);
	// 	pthread_mutex_destroy(&last_mutex);
	// 	return (4);
	// }

	// i = 0;
	// while (i < philos.ph_num)
	// {
	// 	if(pthread_create((t + i), NULL, philosopher, (philos.ph_arr + i)))
	// 	{
	// 		while (i > -1)
	// 		{
	// 			i--;
	// 			pthread_join(t[i], NULL);
	// 		}
	// 	}
	// 	(philos.ph_arr + i)->last = timestamp();
	// 	// gettimeofday(&((philos.ph_arr + i)->last), NULL);
	// 	// printf("Philo %d is created\n", philos.ph_arr[i].index);
	// 	// pthread_detach(t[i]);
	// 	i++;
	// }
	// while (!is_died(&philos)); // should this function be in infinite cycle?
	
	// is_died(&philos);

	// End program	
	all_mutex_delete(&philos, 3);
	free(philos.forks);
	free(philos.last_mutexes);
	free(philos.data.out_m);
	free(philos.ph_arr);
}
