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
#include <pthread.h>

typedef struct s_data {
	long long				start;
	int						to_die;
	int						to_eat;
	int						to_sleep;
	pthread_mutex_t *		out_m;
	// pthread_mutex_t *		last_m;
	int						ph_num;
	int						is_all_ate;
	int						is_to_die;
}	t_data;

typedef struct s_philo {
	long long				last_meal; // last meal
	int						nb_meal;
	// long long				start;
	// int						to_die;
	// int						to_eat;
	// int						to_sleep;
	int						index;
	pthread_mutex_t *		fork_r;
	pthread_mutex_t *		fork_l;
	// pthread_mutex_t *		out;
	pthread_mutex_t *		last_m;
	// int						*is_to_die;
	t_data					*data;
}	t_philo;

typedef struct s_philos {
	t_philo			*ph_arr;
	int				ph_num;
	int				times_to_eat;
	t_data			data;
	pthread_mutex_t *forks;
	pthread_mutex_t *last_mutexes;
	// int		is_to_die;
}	t_philos;

#define TIME_TO_DIE 410
#define TIME_TO_SLEEP 100
#define	TIME_TO_EAT 200
#define NB_OF_PHILO 2
#define T_TO_EAT 1

int			initialize(t_philos *philos);
void		all_mutex_delete(t_philos *philos, int mode);

int			launch(t_philos *philos);
void		*philosopher(void *data);
long long	timestamp(void);
long long	timedif(long long last, long long next);
void		print_action(t_philo *philo, char *msg);


#endif