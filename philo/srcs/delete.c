/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 15:57:30 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	delete_pthread(t_philo **philo, size_t size)
// {
// 	for (int i = 0; i < N_THREAD; i++){
// 		char *ret;
// 		p_join = pthread_join(v[i], (void **)&ret);
// 		free(data[i]);
// 		if (p_join == 0)
// 			printf("finish ID %d, %s\n", i, ret);
// 		else
// 		{
// 			perror("pthread_join");
// 			return (0);
// 		}
// 	}
// }

// void	delete_mutex()
// {
// 	if (pthread_mutex_destroy(&mutex) != 0)
// 	{
// 		perror("pthread_mutex_destroy");
// 		return (0);
// 	}
// }

void	delete_forks(t_fork **forks)
{
	int	i;

	i = 0;
	while (forks[i] != NULL)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	delete_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	delete_table(t_table *table)
{
	// delete_pthread();
	// delete_mutex();
	delete_forks(table->forks);
	delete_philos(table->philos);
	free(table);
}
