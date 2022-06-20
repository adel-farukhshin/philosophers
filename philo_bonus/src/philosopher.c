/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:18:03 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/20 15:18:04 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	check_eaten(t_philo *philo);
static int	check_died(t_philo *philo);

int	philosopher(t_philo *philo)
{
	pthread_t	t;

	if (add_sem(philo))
		exit (1);
	if (pthread_create(&t, NULL, to_stop, philo))
	{
		remove_sem(philo, 4);
		exit (1);
	}
	if (philo->index % 2 == 0)
		smart_sleep(philo, philo->to_eat / 2);
	while (1)
	{
		ph_routine(philo);
		if (check_eaten(philo))
			break ;
		if (check_died(philo))
			break ;
	}
	pthread_join(t, NULL);
	exit (0);
}

static int	check_eaten(t_philo *philo)
{
	sem_wait(philo->is_eaten_s);
	if (philo->is_eaten)
	{
		sem_post(philo->is_eaten_s);
		return (1);
	}
	sem_post(philo->is_eaten_s);
	return (0);
}

static int	check_died(t_philo *philo)
{
	sem_wait(philo->die_s);
	if (philo->is_to_die)
	{
		sem_post(philo->die_s);
		return (1);
	}
	sem_post(philo->die_s);
	return (0);
}
