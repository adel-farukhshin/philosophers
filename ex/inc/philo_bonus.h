/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristi <lchristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:51:11 by lchristi          #+#    #+#             */
/*   Updated: 2022/06/01 12:52:45 by lchristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>

# define NC			"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define DC			"\033[41m"

typedef struct s_philo
{
	int			num_ph;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	int			num_must_eat;
	int			name_ph;
	int			philo_eat;
	int			flag_d;
	pid_t		*pid;
	sem_t		*s_print;
	sem_t		*s_fork;
	pthread_t	t_monitor;
	long long	time_start;
	long long	time_last_eat;
}				t_philo;

int			start_lunch(t_philo *lunch);
void		my_sleep(long long time);
void		print_fork(t_philo *lunch, int c);
void		print_est(t_philo *lunch, int c);
void		all_free(t_philo *lunch);
int			all_kill(t_philo *lunch);
int			check_arg(int argc, char **argv);
int			ft_atoi(const char *nptr);
long long	get_time(void);

/* debug*/
void		print(t_philo *lunch);

#endif