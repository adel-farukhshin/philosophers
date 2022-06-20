#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	create_sem(char *name, sem_t **sem, int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}

void	delete_sem(char *name, sem_t **sem)
{
	sem_close(*sem);
	sem_unlink(name);
}

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

int	add_sem(t_philo *philo)
{
	char	buf[10];

	name_file("last_", buf, philo->index);
	create_sem(buf, &(philo->last_s), 1);
	name_file("die_", buf, philo->index);
	if (create_sem(buf, &(philo->die_s), 1))
	{
		remove_sem(philo, 1);
		return (1);
	}
	name_file("nm_", buf, philo->index);
	if (create_sem(buf, &(philo->nm_s), 1))
	{
		remove_sem(philo, 2);
		return (1);
	}
	name_file("ie_", buf, philo->index);
	if (create_sem(buf, &(philo->is_eaten_s), 1))
	{
		remove_sem(philo, 3);
		return (1);
	}
	return (0);
}

void	remove_sem(t_philo *philo, int mode)
{
	char	buf[10];

	if (mode > 0)
	{
		name_file("last_", buf, philo->index);
		delete_sem(buf, &(philo->last_s));
	}
	if (mode > 1)
	{
		name_file("die_", buf, philo->index);
		delete_sem(buf, &(philo->die_s));
	}
	if (mode > 2)
	{
		name_file("nm_", buf, philo->index);
		delete_sem(buf, &(philo->nm_s));
	}
	if (mode > 3)
	{
		name_file("ie_", buf, philo->index);
		delete_sem(buf, &(philo->is_eaten_s));
	}
}
