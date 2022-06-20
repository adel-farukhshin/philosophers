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
# include <semaphore.h>

// typedef struct s_data {
// 	long long				start;
// 	int						to_die;
// 	int						to_eat;
// 	int						to_sleep;
// 	pthread_mutex_t			*out_m;
// 	int						ph_num;
// 	int						is_all_ate;
//	int						is_to_die;
// }	t_data;

typedef struct s_philo {
	int						index;

	long long				start;
	int						to_die;
	int						to_eat;
	int						to_sleep;
	int						times_to_eat;

	int						nb_meal;
	long long				last_meal;
	
	int						is_eaten;
	int						is_to_die;

	sem_t					*out;
	sem_t					*fork;
	sem_t					*last_s;
	sem_t					*die_s;
	sem_t					*nm_s;
	sem_t					*is_eaten_s;

	// pthread_mutex_t			*fork_r;
	// pthread_mutex_t			*fork_l;
	// pthread_mutex_t			*last_m;
}	t_philo;

typedef struct s_philos {
	// t_philo			*ph_arr;
	int				ph_num;
	t_philo			philo;
	// int				times_to_eat;
	// t_data			data;
	// pthread_mutex_t	*forks;
	// pthread_mutex_t	*last_mutexes;
}	t_philos;



int			initialize(t_philos *philos, int ac, char **av);
void		sem_delete(t_philo *philo, int mode);

int			create_sem(char *name, sem_t **sem, int value);
void		delete_sem(char *name, sem_t **sem);
int			add_sem(t_philo *philo);
void		remove_sem(t_philo *philo, int mode);

int			all_mutex_init(t_philos *philos);
void		all_mutex_delete(t_philos *philos, int mode);

int			ft_atoi(const char *str);

int			launch(t_philos *philos);
int			philosopher(t_philo *philo);
void		*to_stop(void *data);
void		ph_routine(t_philo *philo);

void		smart_sleep(t_philo *philo, long long time);
long long	timestamp(void);
long long	timedif(long long last, long long next);
void		print_action(t_philo *philo, char *msg);

void		name_file(char *src, char dst[], int index);

#endif