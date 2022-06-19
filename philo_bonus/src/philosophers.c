/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:01:55 by bsarai            #+#    #+#             */
/*   Updated: 2022/03/24 12:01:56 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("The number of arguments is incorrect\n");
		return (1);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == -1)
		{
			printf("The argument _%s_ is incorrect\n", argv[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos	philos;

	if (check_args(argc, argv))
		return (1);
	if (initialize(&philos, argc, argv))
		return (2);
	if (launch(&philos))
		return (3);
	
	sem_delete(&(philos.philo), 2);
}
