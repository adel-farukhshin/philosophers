

#include "philosophers.h"
#include <stdio.h>


long long	timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	timedif(long long last, long long next)
{
	return (next - last);
}

void	print_action(t_philo *philo, char *msg)
{
	// lock the writing mutex
	pthread_mutex_lock(philo->out);
	if (!(*(philo->is_to_die)))
	{
		printf("%llu ", timedif(philo->start, timestamp()));
		printf("%d ", philo->index);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(philo->out);
	// unlock the writing mutex
	return ;
}