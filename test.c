
# include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <semaphore.h>
#include <fcntl.h>

sem_t	*sem;
int		to_stop;

void	*routine(void *);
void	add_sem(void);
void	remove_sem(void);

int	main()
{

	to_stop = 0;
	add_sem();

	pthread_t	t;
	
	if (pthread_create(&t, NULL, &routine, NULL))
	{
		return (1);
	}


	// int	i = 0;
	while (1)
	// routine
	{
		sem_wait(sem);
		
		if (to_stop)
		{
			printf("now we are stopping\n");
			break ;
		}
		sem_post(sem);

		// if (i % 1000 == 0)
		// 	printf("%d\n", i);
		// i++;
	}
	
	int	*ret;

	
	if (pthread_join(t, (void **) &ret))
		printf("error\n");
	else
		printf("pthread joined\n");
		
	// free(ret);
	remove_sem();
	return (0);
}

void	*routine(void *data)
{
	int	*ret = data;
	// ret = malloc(sizeof(int));
	// *ret = 1;
	sleep(1);

	sem_wait(sem);
	printf("to_stop is 1 now\n");
	to_stop = 1;
	sem_post(sem);

	return (ret);
}


void	add_sem(void)
{
	char	buf[10] = "se";
	
	sem_unlink(buf);
	sem = sem_open(buf, O_CREAT, 0644, 1);
	
	// print_action(philo, "create die"); // delete
	
}

void	remove_sem(void)
{
	char	buf[10] = "se";

	sem_close(sem);
	sem_unlink(buf);
}

// clang -fsanitize=thread -g -O1 -Wall -Wextra -Werror -pthread test.c 