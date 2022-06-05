/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:16:40 by lchristi          #+#    #+#             */
/*   Updated: 2022/06/01 13:16:43 by lchristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long int	old;
	long int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v' \
					|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		old = num;
		num = num * 10 + (nptr[i++] - '0');
		if ((old < 0 && num > 0) || (old > 0 && num < 0))
			return ((sign == 1) * -1);
	}
	return ((int)(num * sign));
}

void	all_free(t_philo *lunch)
{
	sem_unlink("print");
	sem_unlink("fork");
	sem_close(lunch->s_print);
	sem_close(lunch->s_fork);
	free(lunch->pid);
}

int	all_kill(t_philo *lunch)
{
	int	i;

	i = -1;
	while (++i < lunch->num_ph)
		kill(lunch->pid[i], SIGKILL);
	return (0);
}

void	print_fork(t_philo *lunch, int c)
{
	if (c == 11)
	{
		sem_wait(lunch->s_print);
		printf(NC"%lld %d has taken a 1_fork\n"NC, get_time() - \
		lunch->time_start, lunch->name_ph);
		sem_post(lunch->s_print);
	}
	if (c == 12)
	{
		sem_wait(lunch->s_print);
		printf(NC"%lld %d has taken a 2_fork\n"NC, get_time() - \
		lunch->time_start, lunch->name_ph);
		sem_post(lunch->s_print);
	}
}

void	print_est(t_philo *lunch, int c)
{
	if (c == 2)
	{
		sem_wait(lunch->s_print);
		printf(GREEN"%lld %d is eating\n"NC, get_time() - \
		lunch->time_start, lunch->name_ph);
		sem_post(lunch->s_print);
	}
	else if (c == 3)
	{
		sem_wait(lunch->s_print);
		printf(BLUE"%lld %d is sleeping\n"NC, get_time() - \
		lunch->time_start, lunch->name_ph);
		sem_post(lunch->s_print);
	}
	else if (c == 4)
	{
		sem_wait(lunch->s_print);
		printf(CYAN"%lld %d is thinking\n"NC, get_time() - \
		lunch->time_start, lunch->name_ph);
		sem_post(lunch->s_print);
	}
}
