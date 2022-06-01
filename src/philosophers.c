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

int	init_philos(t_philos *philos, struct timeval tv)
{
	int	i;

	i = 1;
	philos->ph_num = NB_OF_PHILO;
	philos->times_to_eat = T_TO_EAT;
	philos->is_to_die = 0;
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
		philos->ph_arr[i - 1].last.tv_sec = tv.tv_sec;
		philos->ph_arr[i - 1].last.tv_usec = tv.tv_usec;
		philos->ph_arr[i - 1].to_die = TIME_TO_DIE;
		philos->ph_arr[i - 1].to_eat = TIME_TO_EAT;
		philos->ph_arr[i - 1].to_sleep = TIME_TO_SLEEP;
		philos->ph_arr[i - 1].index = i;
		philos->ph_arr[i - 1].is_to_die = &philos->is_to_die;
		i++;
	}
	return (1);
}

void	forks_delete(pthread_mutex_t *forks, int nb)
{
	while (nb > -1)
	{
		pthread_mutex_destroy(forks + nb);
		nb--;
	}
}

pthread_mutex_t *forks_init(t_philos *philos)
{
	pthread_mutex_t *forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philos->ph_num);
	if (!forks)
	{
		free(philos->ph_arr);
		return (NULL);	
	}
	while (i < philos->ph_num)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			forks_delete(forks, i - 1);
			free(philos->ph_arr);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	forks_to_philos(t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 1;
	while (i <= philos->ph_num)
	{
		philos->ph_arr[i - 1].fork_l = forks + i - 1;
		if (i == 1)
			philos->ph_arr[i - 1].fork_r = forks + philos->ph_num - 1;
		else
			philos->ph_arr[i - 1].fork_r = forks + i - 2;
		// printf("philo %d r %p, l %p\n", philos->ph_arr[i - 1].index, philos->ph_arr[i - 1].fork_r, 
		// 		philos->ph_arr[i - 1].fork_l);
		i++;
	}
}

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

int	is_died(t_philos *philos)
{
	int	i;
	struct timeval now;

	gettimeofday(&now, NULL);
	now.tv_sec *= 1000;
	now.tv_usec /= 1000;
	i = 0;
	// printf("now: sec %ld, ms %u\n", tv.tv_sec, tv.tv_usec);
	while (i < philos->ph_num)
	{
		// delta(philos->ph_arr[i].last, tv);
		// printf("now: sec %ld, ms %u; delta: %ld %u\n", tv.tv_sec, tv.tv_usec, 
		// 	tv.tv_sec - philos->ph_arr[i].last.tv_sec, tv.tv_usec - philos->ph_arr[i].last.tv_usec);
		pthread_mutex_lock(((philos->ph_arr) + i)->last_mutex);
		if ((now.tv_sec + now.tv_usec - philos->ph_arr[i].last.tv_sec
			- philos->ph_arr[i].last.tv_usec) > philos->ph_arr->to_die) // tv.tv_sec - philos->ph_arr[i].last.tv_sec * 1000 + 
		{
			pthread_mutex_unlock(((philos->ph_arr) + i)->last_mutex);
			philos->is_to_die = 1;
			pthread_mutex_lock(philos->ph_arr->out);
			printf("%lu %d died\n", now.tv_sec + now.tv_usec 
			- philos->ph_arr[i].start.tv_sec - philos->ph_arr[i].start.tv_usec, philos->ph_arr[i].index);
			pthread_mutex_unlock(philos->ph_arr->out);
			return (1);
		}
		pthread_mutex_unlock(((philos->ph_arr) + i)->last_mutex);
		i++;
	}
	return (0);
}

void	out_to_philos(t_philos *philos, pthread_mutex_t *out)
{
	int	i;

	i = 1;
	while (i <= philos->ph_num)
	{
		philos->ph_arr[i - 1].out = out;
		i++;
	}
}

void	last_mutex_to_philos(t_philos *philos, pthread_mutex_t *last_mutex)
{
	int	i;

	i = 1;
	while (i <= philos->ph_num)
	{
		philos->ph_arr[i - 1].last_mutex = last_mutex;
		i++;
	}
}

int	main()
{
	t_philos philos;
	struct timeval tv;
	int	i = 0;

	// Initialize
	if (gettimeofday(&tv, NULL))
		return (1);
	tv.tv_sec *= 1000;
	tv.tv_usec /= 1000;
	if (!init_philos(&philos, tv))
		return (2);
	// printf("sec %ld, ms: %u\n", tv.tv_sec, tv.tv_usec);

	// Test initializing
	// i = 1;
	// while (i <= philos.ph_num)
	// {
	// 	printf("Phil %d, time: %ld,%u, to_die: %d, to_eat: %d, to_sleep: %d\n", philos.ph_arr[i - 1].index,
	// 	philos.ph_arr[i - 1].start.tv_sec, philos.ph_arr[i - 1].start.tv_usec, philos.ph_arr[i - 1].to_die, 
	// 	philos.ph_arr[i - 1].to_eat, philos.ph_arr[i - 1].to_sleep);
	// 	i++;
	// }


	// Mutex Initialization
	pthread_mutex_t *forks;

	forks = forks_init(&philos);
	if (!forks)
		return (3);
	forks_to_philos(&philos, forks);
	
	// Out Mutex Initialization
	pthread_mutex_t out;

	if (pthread_mutex_init(&out, NULL))
	{	
		forks_delete(forks, philos.ph_num - 1);
		free(forks);
		free(philos.ph_arr);
		return (4);
	}
	out_to_philos(&philos, &out);

	// Last_mutex Initialization
	pthread_mutex_t last_mutex;
	if (pthread_mutex_init(&out, NULL))
	{	
		forks_delete(forks, philos.ph_num - 1);
		free(forks);
		free(philos.ph_arr);
		pthread_mutex_destroy(&out);
		return (4);
	}
	last_mutex_to_philos(&philos, &out);

	// Threads Initialization
	pthread_t *t;
	t = malloc(sizeof(pthread_t) * philos.ph_num); // может это перенести в philos
	if (!t)
	{
		forks_delete(forks, philos.ph_num - 1);
		free(forks);
		free(philos.ph_arr);
		pthread_mutex_destroy(&out);
		pthread_mutex_destroy(&last_mutex);
		return (4);
	}
	i = 0;
	while (i < philos.ph_num)
	{
		if(pthread_create((t + i), NULL, philosopher, (philos.ph_arr + i)))
		{
			while (i > -1)
			{
				i--;
				pthread_join(t[i], NULL);
			}
		}
		// printf("Philo %d is created\n", philos.ph_arr[i].index);
		// pthread_detach(t[i]);
		i++;
	}
	while (!is_died(&philos)); // should this function be in infinite cycle?
	
	// is_died(&philos);

	// End program
	i = 0;
	while (i < philos.ph_num)
	{
		if (pthread_join(t[i], NULL))
			perror("Failed to join error");
		else
			// printf("Philo %d is deleted\n", i);
			
		i++;
	} // разница между detached и join в том, что в первом случае ресурсы освобождаются сразу по выходу из треда, в то время как, во втором случае необходим вызов join
	
	// pthread_exit(0);


	// printf("time at exit: sec %ld, ms %u\n", tv.tv_sec, tv.tv_usec);
	free(t);

	forks_delete(forks, philos.ph_num - 1);
	free(forks);
	free(philos.ph_arr);
	pthread_mutex_destroy(&out);
	pthread_mutex_destroy(&last_mutex);
}
