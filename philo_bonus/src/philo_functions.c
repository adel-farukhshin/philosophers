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
		sem_wait(philo->nm_s);
		if (philo->times_to_eat != -1 && philo->nb_meal == philo->times_to_eat)
		{
			sem_wait(philo->is_eaten_s);
			philo->is_eaten = 1;
			sem_post(philo->is_eaten_s);
			break ;
		}
		sem_post(philo->nm_s);
		sem_wait(philo->last_s);
		if (timestamp() - philo->last_meal >= philo->to_die)
		{
			sem_wait(philo->die_s);
			philo->is_to_die = 1;
			sem_post(philo->die_s);
			sem_wait(philo->out);
			printf("%llu %d is_died\n", timestamp() - philo->start, philo->index);
			break ;
		}
		sem_post(philo->last_s);
	}
	remove_sem(philo, 4);
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
	// routine
	{
		ph_routine(philo);

		sem_wait(philo->is_eaten_s);
		if (philo->is_eaten)
		{
			sem_post(philo->is_eaten_s);
			break ;
		}
		sem_post(philo->is_eaten_s);

		sem_wait(philo->die_s);
		if (philo->is_to_die)
		{
			sem_post(philo->die_s);
			break;
		}
		sem_post(philo->die_s);
	}
	
	pthread_join(t, NULL);

	// if (pthread_join(t, NULL)) // error
	// {
	// 	printf("a\n"); // delete
	// 	return (1);
	// }
	// else
	// {
	// 	printf("b\n");
	// 	return (0);
	// }
	exit (0);
}



/*
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
		remove_sem(philo, 1);
		return (1);
	}
	// print_action(philo, "create die"); // delete
	return (0);
}
*/






/*
void	remove_sem(t_philo *philo, int mode)
{
	char	buf[10];

	if (mode > 0)
	{
		sem_close(philo->last_s);
		name_file("last_", buf, philo->index);
		sem_unlink(buf);
	}
	if (mode > 1)
	{
		sem_close(philo->die_s);
		name_file("die_", buf, philo->index);
		sem_unlink(buf);
	}
}
*/


