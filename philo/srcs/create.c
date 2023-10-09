/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 14:59:56 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(t_fork **forks, int size, t_philo_ability ability)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * size + 1);
	i = 0;
	while (i < size)
	{
		philos[i] = new_philo(i, forks[i], forks[(i + 1) % size], ability);
		i++;
	}
	return (philos);
}

t_fork	**create_forks(int size)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork) * (size + 1));
	i = 0;
	while (i < size)
	{
		forks[i] = new_fork();
		i++;
	}
	forks[size] = NULL;
	return (forks);
}
