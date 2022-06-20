/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:14:57 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/20 21:14:59 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n));
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	timedif(long long past, long long pres)
{
	return (pres - past);
}

void	print_action(t_philo *philo, char *msg)
{
	if (!philo->data->out_m)
		return ;
	pthread_mutex_lock(philo->data->out_m);
	if (!(philo->data->is_to_die))
	{
		printf("%llu ", timedif(philo->data->start, timestamp()));
		printf("%d ", philo->index);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(philo->data->out_m);
	return ;
}
