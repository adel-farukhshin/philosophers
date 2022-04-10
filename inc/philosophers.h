/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:04:20 by bsarai            #+#    #+#             */
/*   Updated: 2022/03/24 12:04:21 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <sys/time.h>

typedef struct s_philo {
	struct timeval start;
	int		to_die;
	int		to_eat;
	int		to_sleep;
	int		index;
}	t_philo;

typedef struct s_philos {
	t_philo	*ph_arr;
	int		ph_num;
	int		times_to_eat;
}	t_philos;

#define TIME_TO_DIE 10
#define TIME_TO_SLEEP 1
#define	TIME_TO_EAT 1
#define NB_OF_PHILO 5
#define T_TO_EAT -1

#endif