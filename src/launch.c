
#include "philosophers.h"
#include <stdlib.h>

int	is_died(t_philos *philos)
{
	int	i;
	// struct timeval now;
	long long	now;
	
	i = 0;
	// printf("now: sec %ld, ms %u\n", tv.tv_sec, tv.tv_usec);
	while (i < philos->ph_num && !(philos->data.is_to_die))
	{
		// gettimeofday(&now, NULL);
		// now.tv_sec *= 1000;
		// now.tv_usec /= 1000;

		now = timestamp();
		// delta(philos->ph_arr[i].last, tv);
		// printf("now: sec %ld, ms %u; delta: %ld %u\n", tv.tv_sec, tv.tv_usec, 
		// 	tv.tv_sec - philos->ph_arr[i].last.tv_sec, tv.tv_usec - philos->ph_arr[i].last.tv_usec);
		pthread_mutex_lock(((philos->ph_arr) + i)->last_m);
		if (timedif(philos->ph_arr[i].last_meal, now) >= philos->data.is_to_die) // tv.tv_sec - philos->ph_arr[i].last.tv_sec * 1000 + 
		{
			pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
			
			print_action(philos->ph_arr + i, "died");
			philos->data.is_to_die = 1;
			// pthread_mutex_lock(philos->ph_arr->out);
			// printf("%llu ", timedif(philos->ph_arr->start, timestamp()));
			// printf("%d ", philos->ph_arr[i].index);
			// printf("died\n");
			// pthread_mutex_unlock(philos->ph_arr->out);
			return (1);
		}
		pthread_mutex_unlock(((philos->ph_arr) + i)->last_m);
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
		i++;
	}
	while (!is_died(philos));
	error = thread_delete(t, philos->ph_num - 1);
	free(t);
	return (error);
}