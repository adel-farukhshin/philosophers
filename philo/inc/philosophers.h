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

# include <sys/time.h>
# include <pthread.h>

typedef struct s_data {
	long long				start;
	int						to_die;
	int						to_eat;
	int						to_sleep;
	pthread_mutex_t			*out_m;
	int						ph_num;
	int						is_all_ate;
	int						is_to_die;
}	t_data;

typedef struct s_philo {
	long long				last_meal;
	int						nb_meal;
	int						index;
	pthread_mutex_t			*fork_r;
	pthread_mutex_t			*fork_l;
	pthread_mutex_t			*last_m;
	t_data					*data;
}	t_philo;

typedef struct s_philos {
	t_philo			*ph_arr;
	int				ph_num;
	int				times_to_eat;
	t_data			data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_mutexes;
}	t_philos;

int			initialize(t_philos *philos, int ac, char **av);
void		all_mutex_delete(t_philos *philos, int mode);

int			ft_atoi(const char *str);

int			launch(t_philos *philos);
void		*philosopher(void *data);
long long	timestamp(void);
long long	timedif(long long last, long long next);
void		print_action(t_philo *philo, char *msg);

#endif