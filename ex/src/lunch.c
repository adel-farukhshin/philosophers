/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:04:04 by lchristi          #+#    #+#             */
/*   Updated: 2022/06/01 13:04:06 by lchristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	my_delay(t_philo *lunch)
{
	if (lunch->num_ph % 5 == 0)
		usleep(15000);
	if (lunch->num_ph % 2 != 0)
		usleep(15000);
}

void	*death_monitor(void *lunch)
{
	t_philo	*tmp;

	tmp = (t_philo *)lunch;
	while (1)
	{
		if (tmp->num_must_eat)
			if (tmp->philo_eat == tmp->num_must_eat)
				break ;
		if (get_time() - tmp->time_last_eat > tmp->tt_die)
		{
			tmp->flag_d = 1;
			sem_wait(tmp->s_print);
			printf(RED"%lld %d died\n"NC, get_time() - tmp->time_start, \
			tmp->name_ph);
			break ;
		}
	}
	if (tmp->flag_d)
		exit (1);
	else
		exit (0);
}

int	eat_sleep_think(t_philo *lunch)
{
	sem_wait(lunch->s_fork);
	print_fork(lunch, 11);
	if (lunch->num_ph == 1)
	{
		sem_post(lunch->s_fork);
		return (1);
	}
	sem_wait(lunch->s_fork);
	print_fork(lunch, 12);
	print_est(lunch, 2);
	lunch->time_last_eat = get_time();
	my_sleep(lunch->tt_eat);
	sem_post(lunch->s_fork);
	sem_post(lunch->s_fork);
	lunch->philo_eat++;
	print_est(lunch, 3);
	my_sleep(lunch->tt_sleep);
	print_est(lunch, 4);
	return (0);
}

int	philo_lunch(t_philo *lunch)
{
	if (pthread_create(&lunch->t_monitor, NULL, &death_monitor, lunch))
		return (1);
	if (lunch->num_ph % 2 == 0 && lunch->name_ph % 2 == 0)
		my_sleep(lunch->tt_eat / 2);
	while (lunch->flag_d != 1)
	{
		if (lunch->num_must_eat)
			if (lunch->philo_eat == lunch->num_must_eat)
				break ;
		if (eat_sleep_think(lunch))
			break ;
	}
	if (pthread_join(lunch->t_monitor, NULL))
		return (1);
	return (0);
}

int	start_lunch(t_philo *lunch)
{
	int	i;
	int	status;

	i = -1;
	lunch->time_start = get_time();
	while (++i < lunch->num_ph)
	{
		lunch->pid[i] = fork();
		if (lunch->pid[i] == -1)
			return (1);
		if (lunch->pid[i] == 0)
		{
			lunch->name_ph = i + 1;
			lunch->time_last_eat = lunch->time_start;
			if (philo_lunch(lunch))
				return (1);
		}
		my_delay(lunch);
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
			return (all_kill(lunch));
	}
	return (0);
}
