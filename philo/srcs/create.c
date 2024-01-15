/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/29 14:12:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

#define ERROR_MES_CREATE_THREAD "pthread fail\n"

int	create_pthread(t_philo **philos)
{
	int		i;
	int		p_create;

	i = 0;
	while (i < philos[0]->table->config.n_philos)
	{
		p_create = pthread_create(&philos[i]->living, NULL,
				simulation, philos[i]);
		if (p_create != 0)
		{
			write(STDERR_FILENO, ERROR_MES_CREATE_THREAD,
				ft_strlen(ERROR_MES_CREATE_THREAD));
			pthread_mutex_lock(&philos[i]->table->get_data);
			philos[i]->table->is_error = true;
			pthread_mutex_unlock(&philos[i]->table->get_data);
			return (i);
		}
		i++;
	}
	return (i);
}

t_fork	**create_forks(int n_philos)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork) * n_philos);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		forks[i] = new_fork();
		if (forks[i] == NULL)
		{
			delete_forks(forks);
			return (NULL);
		}
		if (i % 2 == 0)
			forks[i]->last_eat_philo = i + 1;
		else
			forks[i]->last_eat_philo = i + 2;
		i++;
	}
	if (i % 2 != 0)
		forks[i - 1]->last_eat_philo = i;
	return (forks);
}

t_philo	**create_philos(t_fork **forks,
							t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * table->config.n_philos);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table->config.n_philos)
	{
		philos[i] = new_philo(i + 1, forks[i],
				forks[(i + 1) % table->config.n_philos],
				table);
		if (philos[i] == NULL)
		{
			delete_philos(philos, i);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
