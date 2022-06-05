/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:03:26 by lchristi          #+#    #+#             */
/*   Updated: 2022/06/01 13:03:28 by lchristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print(t_philo *lunch)
{
	printf(GREEN"num of philo %d\n"NC, lunch->num_ph);
	printf(RED"time to die %d\n"NC, lunch->tt_die);
	printf("time to eat %d\n", lunch->tt_eat);
	printf("time to sleep %d\n", lunch->tt_sleep);
	printf(YELLOW"time to must eat %d\n"NC, lunch->num_must_eat);
	printf("begin time = %lld\n", lunch->time_start);
	printf("start\n");
}
