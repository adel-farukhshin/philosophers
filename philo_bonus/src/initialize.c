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
#include <fcntl.h>

int	initialize(t_philos *philos, int ac, char **av)
{
	philos->ph_num = ft_atoi(av[1]);
	philos->philo.to_die = ft_atoi(av[2]);
	philos->philo.to_eat = ft_atoi(av[3]);
	philos->philo.to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->philo.times_to_eat = ft_atoi(av[5]);
	else
		philos->philo.times_to_eat = -1;
	philos->philo.nb_meal = 0;
	philos->philo.is_eaten = 0;
	philos->philo.is_to_die = 0;
	if (create_sem("out", &(philos->philo.out), 1))
		return (1);
	if (create_sem("fork", &(philos->philo.fork), philos->ph_num))
	{
		sem_delete(&(philos->philo), 1);	
		return (1);
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