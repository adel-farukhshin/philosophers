

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

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

void	print_action(t_philo *philo, char *msg)
{
	sem_wait(philo->out);
	printf("%llu %d %s\n", timestamp() - philo->start, philo->index, msg);
	sem_post(philo->out);
}

void	smart_sleep(t_philo *philo, long long time)
{
	long long	i;
	long long	a;

	i = timestamp();
	while (1)
	// while (!(philo->is_to_die))
	{
		a = timestamp();
		sem_wait(philo->die_s);
		sem_wait(philo->is_eaten_s);
		if (a - i >= time || philo->is_to_die || (philo->times_to_eat != -1 && philo->is_eaten))
		{
			sem_post(philo->is_eaten_s);
			sem_post(philo->die_s);
			break ;
		}
		sem_post(philo->die_s);
		sem_post(philo->is_eaten_s);
		usleep(500);
	}
}