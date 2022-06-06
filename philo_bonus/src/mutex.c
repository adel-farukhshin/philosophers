/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 12:58:26 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/05 12:58:27 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
/*
void	mutex_delete(pthread_mutex_t *mutex, int nb)
{
	while (nb > -1)
	{
		pthread_mutex_destroy(mutex + nb);
		nb--;
	}
}

int	mutex_init(pthread_mutex_t **type, int nb)
{
	int				i;
	pthread_mutex_t	*mutex;

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

int	all_mutex_init(t_philos *philos)
{
	if (mutex_init(&(philos->forks), philos->ph_num))
		return (1);
	if (mutex_init(&(philos->last_mutexes), philos->ph_num))
	{
		all_mutex_delete(philos, 1);
		return (2);
	}
	if (mutex_init(&(philos->data.out_m), 1))
	{
		all_mutex_delete(philos, 2);
		return (3);
	}
	return (0);
}
*/