
#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	is_all_ate(t_philos *philos)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (philos->times_to_eat != -1 && i < philos->ph_num)
	{
		if (((philos->ph_arr) + i)->nb_meal >= philos->times_to_eat)
			nb++;
		i++;
	}
	if (nb == philos->ph_num)
	{
		philos->data.is_all_ate = 1;
		return (1);
	}
	return (0);
}

int	is_died(t_philos *philos)
{
	int	i;
	// long long	now;
	
	i = 0;
	while (i < philos->ph_num && !(philos->data.is_to_die) && !(philos->data.is_all_ate))
	{
		// now = timestamp();
		pthread_mutex_lock(((philos->ph_arr) + i)->last_m); // one last_m
		if (timedif(philos->ph_arr[i].last_meal, timestamp()) >= philos->data.to_die)
		{
			// printf("last %llu, now %llu, %d\n", philos->ph_arr[i].last_meal, now, philos->data.is_to_die);
			pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
			print_action(philos->ph_arr + i, "died");
			philos->data.is_to_die = 1;
			// usleep(100); // not commented
			return (1); // break
			// break ;
		}
		// if (philos->data.is_to_die)
		// 	break ;
		pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
		if (is_all_ate(philos))
			return (2);
		i++;
	}
	return (0);
}

int	thread_delete(pthread_t *t, int nb)
{
	int error;

	error = 0;
	while (nb > -1)
	{
		if (pthread_join(t[nb], NULL))
			error = 2;
		nb--;
	}
	return (error);
}

int		launch(t_philos *philos)
{	
	// Threads Initialization
	pthread_t 	*t;
	int			i;
	int			error;
	
	t = malloc(sizeof(pthread_t) * philos->ph_num);
	if (!t)
		return (1);
	i = 0;
	philos->data.start = timestamp();
	// printf("%llu\n", philos->data.start);
	while (i < philos->ph_num)
	{
		if(pthread_create((t + i), NULL, philosopher, (philos->ph_arr + i)))
		{
			if (thread_delete(t, i - 1))
			{
				free (t);
				return (2);
			}
		}
		(philos->ph_arr + i)->last_meal = timestamp();
		// printf("%lld\n", (philos->ph_arr + i)->last_meal);
		i++;
	}
	while (!is_died(philos));
	error = thread_delete(t, philos->ph_num - 1);
	free(t);
	return (error);
}