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
		philos->ph_arr[i - 1].nb_meal = 0;
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

void	all_mutex_delete(t_philos *philos, int mode)
{
	if (mode > 0)
		mutex_delete(philos->forks, philos->ph_num - 1);
	if (mode > 1)
		mutex_delete(philos->last_mutexes, philos->ph_num - 1);
	if (mode > 2)
		mutex_delete(philos->data.out_m, 1 - 1);
}

int		initialize(t_philos *philos, int ac, char **av)
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
{
	philos->ph_num = ft_atoi(av[1]);
	philos->data.ph_num = ft_atoi(av[1]);
	philos->data.to_die = ft_atoi(av[2]);
	philos->data.to_eat = ft_atoi(av[3]);
	philos->data.to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->times_to_eat = ft_atoi(av[5]);
	else
		philos->times_to_eat = -1;
	// philos->data.start = timestamp(); // need to change?
	philos->data.is_all_ate = 0;
	philos->data.is_to_die = 0;

	if (mutex_init(&(philos->forks), philos->ph_num))
		return (1);
	if (mutex_init(&(philos->last_mutexes), philos->ph_num))
	{
		mutex_delete(philos->forks, philos->ph_num - 1);
		return (2);
	}
	if (mutex_init(&(philos->data.out_m), 1))
	{
		mutex_delete(philos->forks, philos->ph_num - 1);
		mutex_delete(philos->last_mutexes, philos->ph_num - 1);
		return (3);
	}
	if (init_philos(philos))
	{
		mutex_delete(philos->forks, philos->ph_num - 1);
		mutex_delete(philos->last_mutexes, philos->ph_num - 1);
		mutex_delete(philos->data.out_m, 1 - 1);
		return (4);
	}
	return (0);
}

// #include <stdio.h>
//
// int	main()
// {
// 	t_philos	philos;
	
// 	initialize(&philos);
// 	int	i = 0;

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
// 	mutex_delete(philos.forks, philos.ph_num - 1);
// 	mutex_delete(philos.last_mutexes, philos.ph_num - 1);
// 	mutex_delete(philos.data.out_m, 1 - 1);

// 	free(philos.forks);
// 	free(philos.last_mutexes);
// 	free(philos.data.out_m);
// 	free(philos.ph_arr);
// }