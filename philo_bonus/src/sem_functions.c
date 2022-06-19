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
