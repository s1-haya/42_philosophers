/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/23 15:48:21 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	delete_

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
	free(table);
}
