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
// #include <sys/time.h>
#include <unistd.h>
// #include <pthread.h>
#include <stdlib.h>

#include "philosophers.h"


int	main()
{
	t_philos philos;
	// int	i = 0;

	// Initialize
	if (initialize(&philos))
		return (1);

	if (launch(&philos))
		return (2);

	// End program	
	all_mutex_delete(&philos, 3);
	free(philos.forks);
	free(philos.last_mutexes);
	free(philos.data.out_m);
	free(philos.ph_arr);
}
