

#include "philosophers.h"
#include <stdio.h>

void	sem_delete(t_philo *philo, int mode)
{
	if (mode > 0)
	{
		sem_close(philo->out);
		sem_unlink("out");
	}
	if (mode > 1)
	{
		sem_close(philo->fork);
		sem_unlink("fork");
	}
}

int	ft_atoi(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n));
}

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

