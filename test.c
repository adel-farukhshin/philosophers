
# include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

sem_t	*sem;
int		to_stop;

void	*routine(void *);
void	add_sem(void);
void	remove_sem(void);

int	main()
{
	pid_t pid;

	pid = fork();

	if (!pid)
	{
		to_stop = 0;
		add_sem();

		pthread_t	t;
		
		if (pthread_create(&t, NULL, &routine, NULL))
		{
			return (1);
		}
		// pthread_detach(t);


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
		printf("after while cycle\n");
		
		int	*ret;

		if (pthread_join(t, (void **) &ret))
			printf("error\n");
		else
			printf("pthread joined\n");
		printf("exit code %d\n", *ret);

		free(ret);
		printf("after pthread\n");
		remove_sem();
		return (0);
	}

	wait(&pid);
	// int	*ret;

	// printf("before pthread_join\n");

	
		
	

	// printf("before remove_sem %d\n", *ret);
	// printf("before remove_sem\n");
	// free(ret);
	
	printf("before end program\n");
	return (0);
}

void	*routine(void *data)
{
	int	*ret = data;
	// (void ) ret;
	ret = malloc(sizeof(int));
	*ret = 1;
	sleep(1);

	sem_wait(sem);
	printf("to_stop is 1 now\n");
	to_stop = 1;
	sem_post(sem);

	return (ret);
	// exit (*ret);
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