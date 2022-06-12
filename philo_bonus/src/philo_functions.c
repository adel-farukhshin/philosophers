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

/*

pthread_mutex_t	*min(pthread_mutex_t *r, pthread_mutex_t *l)
{
	if (r < l)
		return (r);
	else
		return (l);
}

pthread_mutex_t	*max(pthread_mutex_t *r, pthread_mutex_t *l)
{
	if (r > l)
		return (r);
	else
		return (l);
}
*/
void	smart_sleep(t_philo *philo, long long time)
{
	long long	i;
	long long	a;

	i = timestamp();
	while (!(philo->is_to_die))
	{
		a = timestamp();
		if (a - i >= time)
			break ;
		usleep(50);
	}
}
/*
void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->last_m);
	print_action(philo, "is eating");
	philo->last_meal = timestamp();
	pthread_mutex_unlock(philo->last_m);
	philo->nb_meal += 1;
	smart_sleep(philo->data->to_eat, philo);
}

*/

// void	*philosopher(void *data)
// {
// 	t_philo	*philo;

// 	philo = data;
// 	if (philo->index % 2 == 0)
// 		usleep(20);
// 	if (philo->data->ph_num == 1)
// 	{
// 		smart_sleep(philo->data->to_die, philo);
// 		philo->data->is_to_die = 1;
// 	}
// 	while (!(philo->data->is_to_die) && !(philo->data->is_all_ate))
// 	{
// 		pthread_mutex_lock(min(philo->fork_r, philo->fork_l));
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(max(philo->fork_r, philo->fork_l));
// 		print_action(philo, "has taken a fork");
// 		ph_eat(philo);
// 		pthread_mutex_unlock(max(philo->fork_r, philo->fork_l));
// 		pthread_mutex_unlock(min(philo->fork_r, philo->fork_l));
// 		print_action(philo, "is sleeping");
// 		smart_sleep(philo->data->to_sleep, philo);
// 		print_action(philo, "is thinking");
// 	}
// 	return (0);
// }


void	*to_stop(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		// Check times of eating
		// if (philo->nb_meal == philo->times_to_eat)
		// {
		// 	philo->is_eaten = 1;
		// 	break ;
		// }
		// Check is died
		if (timestamp() - philo->last_meal >= philo->to_die)
		{
			philo->is_to_die = 1;
			sem_wait(philo->out);
			printf("%llu %d is_died\n", timestamp() - philo->start, philo->index);
			break ;
		}
		
	}


	// Maybe put it in cycle?
	if (philo->is_to_die)
		exit (1);
	else
		exit (0);
}

void	ph_routine(t_philo *philo)
{
	sem_wait(philo->fork);
	print_action(philo, "has taken a 1_fork");
	sem_wait(philo->fork);
	print_action(philo, "has taken a 2_fork");

	print_action(philo, "is eating");
	philo->last_meal = timestamp();
	philo->nb_meal++;
	smart_sleep(philo, philo->to_eat);

	sem_post(philo->fork);
	sem_post(philo->fork);

	print_action(philo, "is sleeping");
	smart_sleep(philo, philo->to_sleep);

	print_action(philo, "is thinking");
}

int	add_sem(t_philo *philo);

int	philosopher(t_philo *philo)
{
	pthread_t	t;
	
	if (add_sem(philo))
		return (1);

	if (pthread_create(&t, NULL, to_stop, philo))
		return (1);

	while (!philo->is_to_die)
	// routine
	{
		ph_routine(philo);
	}
	
	if (pthread_join(t, NULL))
	{
		printf("a\n"); // delete
		return (1);
	}
	else
	{
		printf("b\n");
		return (0);
	}
	// return (0);
}

int	add_sem(t_philo *philo)
{
	char	buf[10];

	name_file("last_", buf, philo->index);
	sem_unlink(buf);
	philo->last_s = sem_open(buf, O_CREAT, 0644, 1);
	if (philo->last_s == SEM_FAILED)
		return (1);
	// print_action(philo, "create last"); // delete

	name_file("die_", buf, philo->index);
	sem_unlink(buf);
	philo->die_s = sem_open(buf, O_CREAT, 0644, 1);
	if (philo->die_s == SEM_FAILED)
	{
		sem_close(philo->last_s);	
		return (1);
	}
	// print_action(philo, "create die"); // delete
	return (0);
}