

#include "philosophers.h"
#include <stdio.h>


long long	timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	timedif(long long past, long long pres)
{
	return (pres - past);
}

void	print_action(t_philo *philo, char *msg)
{
	// lock the writing mutex
	pthread_mutex_lock(philo->data->out_m);
	if (!(philo->data->is_to_die))
	{
		printf("%llu ", timedif(philo->data->start, timestamp()));
		printf("%d ", philo->index);
		printf("%s\n", msg);
	}
	// unlock the writing mutex
	pthread_mutex_unlock(philo->data->out_m);
	return ;
}