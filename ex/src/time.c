/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:15:28 by lchristi          #+#    #+#             */
/*   Updated: 2022/06/01 13:15:30 by lchristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}
