/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:26:58 by bsarai            #+#    #+#             */
/*   Updated: 2022/04/10 15:26:59 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	change_eaten(t_philo *philo);
static int	change_died(t_philo *philo);

void	*to_stop(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (change_eaten(philo))
			break ;
		if (change_died(philo))
			break ;
	}
	remove_sem(philo, 4);
	if (philo->is_to_die)
		exit (1);
	else
		exit (0);
}

static int	change_eaten(t_philo *philo)
{
	sem_wait(philo->nm_s);
	if (philo->times_to_eat != -1 && philo->nb_meal == philo->times_to_eat)
	{
		sem_wait(philo->is_eaten_s);
		philo->is_eaten = 1;
		sem_post(philo->is_eaten_s);
		return (1);
	}
	sem_post(philo->nm_s);
	return (0);
}

static int	change_died(t_philo *philo)
{
	sem_wait(philo->last_s);
	if (timestamp() - philo->last_meal >= philo->to_die)
	{
		sem_wait(philo->die_s);
		philo->is_to_die = 1;
		sem_post(philo->die_s);
		sem_wait(philo->out);
		printf("%llu %d is_died\n", timestamp() - philo->start, philo->index);
		return (1);
	}
	sem_post(philo->last_s);
	return (0);
}

void	ph_routine(t_philo *philo)
{
	sem_wait(philo->fork);
	print_action(philo, "has taken a 1_fork");
	sem_wait(philo->fork);
	print_action(philo, "has taken a 2_fork");
	print_action(philo, "is eating");
	sem_wait(philo->last_s);
	philo->last_meal = timestamp();
	sem_post(philo->last_s);
	smart_sleep(philo, philo->to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	sem_wait(philo->nm_s);
	philo->nb_meal++;
	sem_post(philo->nm_s);
	print_action(philo, "is sleeping");
	smart_sleep(philo, philo->to_sleep);
	print_action(philo, "is thinking");
}
