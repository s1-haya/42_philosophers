/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/25 15:33:16 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_fork(t_fork *fork)
{
	pthread_mutex_destroy(&(fork->fork));
	free(fork);
}

void	delete_forks(t_fork **forks)
{
	int	i;

	i = 0;
	while (forks[i] != NULL)
	{
		delete_fork(forks[i]);
		i++;
	}
	free(forks);
}

void	delete_table(t_table *table)
{
	pthread_mutex_destroy(&(table->mes));
	pthread_mutex_destroy(&(table->read));
	free(table);
}

void	delete_philos(t_philo **philos, int index)
{
	int	i;

	i = 0;
	delete_table(philos[i]->table);
	while (i < index)
	{
		delete_fork(philos[i]->left);
		free(philos[i]);
		i++;
	}
	free(philos);
}
