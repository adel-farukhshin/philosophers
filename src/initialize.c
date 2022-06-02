/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:59:28 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/02 12:59:29 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <unistd.h>

// long long	timestamp(void)
// {
// 	struct timeval tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }

int	init_philos(t_philos *philos)
{
	int	i;

	i = 1;
	philos->ph_arr = malloc(sizeof(t_philo) * philos->ph_num);
	if (!philos->ph_arr)
		return (1);
	while (i <= philos->ph_num)
	{
		philos->ph_arr[i - 1].index = i;
		philos->ph_arr[i - 1].last_m = philos->last_mutexes + i - 1;
		philos->ph_arr[i - 1].fork_l = philos->forks + i - 1;
		if (i == 1)
			philos->ph_arr[i - 1].fork_r = philos->forks + philos->ph_num - 1;
		else
			philos->ph_arr[i - 1].fork_r = philos->forks + i - 2;
		philos->ph_arr[i - 1].data = &(philos->data);
		i++;
	}
	return (0);
}

void	mutex_delete(pthread_mutex_t *mutex, int nb)
{
	while (nb > -1)
	{
		pthread_mutex_destroy(mutex + nb);
		nb--;
	}
	free(mutex + nb); // check
}

int mutex_init(pthread_mutex_t **type, int nb)
{
	int	i;
	pthread_mutex_t *mutex;

	i = 0;

	mutex = malloc(sizeof(pthread_mutex_t) * nb);
	if (!mutex)
		return (1);	
	while (i < nb)
	{
		if (pthread_mutex_init(mutex + i, NULL))
		{
			mutex_delete(mutex, i - 1);
			return (2);
		}
		i++;
	}
	*type = mutex;
	return (0);
}

// void	forks_delete(pthread_mutex_t *forks, int nb)
// {
// 	while (nb > -1)
// 	{
// 		pthread_mutex_destroy(forks + nb);
// 		nb--;
// 	}
// 	free(forks + nb); // check
// }

// int	forks_init(t_philos *philos)
// {
// 	int	i;
// 	i = 0;
// 	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->ph_num);
// 	if (!philos->forks)
// 		return (1);	
// 	while (i < philos->ph_num)
// 	{
// 		if (pthread_mutex_init(philos->forks + i, NULL))
// 		{
// 			forks_delete(philos->forks, i - 1);
// 			return (2);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		initialize(t_philos *philos)
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
{
	philos->ph_num = NB_OF_PHILO;
	philos->data.to_eat = TIME_TO_EAT;
	philos->data.to_die = TIME_TO_DIE;
	philos->data.to_sleep = TIME_TO_SLEEP;
	philos->times_to_eat = T_TO_EAT;
	philos->data.start = timestamp(); // need to change?
	philos->data.is_to_die = 0;

	if (mutex_init(&(philos->forks), philos->ph_num))
		return (1);
	if (mutex_init(&(philos->last_mutexes), philos->ph_num))
	{
		mutex_delete(philos->forks, philos->ph_num);
		return (2);
	}
	if (mutex_init(&(philos->data.out_m), 1))
	{
		mutex_delete(philos->forks, philos->ph_num);
		mutex_delete(philos->last_mutexes, philos->ph_num);
		return (3);
	}
	if (init_philos(philos))
	{
		mutex_delete(philos->forks, philos->ph_num);
		mutex_delete(philos->last_mutexes, philos->ph_num);
		mutex_delete(philos->data.out_m, 1);
		return (4);
	}
	return (0);
}

// #include <stdio.h>
//
// int	main()
// {
// 	t_philos	philos;
//	
// 	initialize(&philos);
// 	int	i = 0;
//
// 	printf("ph_arr %p; ph_num %d; times_to_eat %d\n", philos.ph_arr,
// 		philos.ph_num, philos.times_to_eat);
// 	printf("ph_forks %p; last_mutexes %p\n", philos.forks, philos.last_mutexes);
// 	printf("data %p\n", &(philos.data));
// 	while (i < philos.ph_num)
// 	{
// 		printf("--------------\n");
// 		printf("Philo %d\n", philos.ph_arr[i].index);
// 		printf("fork_l %p\n", philos.ph_arr[i].fork_l);
// 		printf("fork_r %p\n", philos.ph_arr[i].fork_r);
// 		printf("last_m %p\n", philos.ph_arr[i].last_m);
// 		printf("Start %llu, to_die %d, to_eat %d, to_sleep %d\n",
// 			philos.ph_arr[i].data->start, philos.ph_arr[i].data->to_die,
// 			philos.ph_arr[i].data->to_eat, philos.ph_arr[i].data->to_sleep);
// 		printf("Out_m %p\n", philos.ph_arr[i].data->out_m);
// 		printf("Is_to_die %d\n", philos.ph_arr[i].data->is_to_die);
// 		i++;
// 	}
// 	mutex_delete(philos.forks, philos.ph_num);
// 	mutex_delete(philos.last_mutexes, philos.ph_num);
// 	mutex_delete(philos.data.out_m, 1);
// 	free(philos.ph_arr);
// }