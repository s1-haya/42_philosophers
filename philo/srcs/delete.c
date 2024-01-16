/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:39 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/16 14:51:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
	pthread_mutex_destroy(&(table->print_message));
	pthread_mutex_destroy(&(table->get_data));
	free(table);
}

void	delete_philos(t_philo **philos, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		delete_fork(philos[i]->left);
		free(philos[i]);
		i++;
	}
	free(philos);
}
