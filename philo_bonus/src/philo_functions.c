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
