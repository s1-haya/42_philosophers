/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/15 11:12:36 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_pthread(t_philo **philo, int n_philo)
{
	int		p_join;
	int		i;
	char	*ret;

	i = 0;
	while (i < n_philo)
	{
		p_join = pthread_join(philo[i]->living, (void **)&ret);
		if (p_join == 0)
			printf("finish ID %d, %s\n", i, ret);
		else
		{
			perror("pthread_join");
			return ;
		}
		i++;
	}
}

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
