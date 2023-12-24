/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/23 16:58:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERROR_MES_CREATE_THREAD "pthread fail"

int	create_pthread(t_philo **philos)
{
	int		i;
	int		p_create;

	i = 0;
	while (philos[i] != NULL)
	{
		p_create = pthread_create(&philos[i]->living, NULL, simulation, philos[i]);
		if (p_create != 0)
		{
			write(STDERR_FILENO, ERROR_MES_CREATE_THREAD, ft_strlen(ERROR_MES_CREATE_THREAD));
			pthread_mutex_lock(&philos[i]->table->table);
			philos[i]->table->is_error = true;
			pthread_mutex_unlock(&philos[i]->table->table);
			return (i);
		}
		i++;
	}
	return (i);
}

t_fork **create_forks(int n_philos)
{
	t_fork **forks;
	int i;

	forks = malloc(sizeof(t_fork) * (n_philos + 1));
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
	forks[n_philos] = NULL;
	return (forks);
}

t_philo **create_philos(t_fork **forks,
						t_table *table)
{
	t_philo **philos;
	int i;

	philos = malloc(sizeof(t_philo) * table->ability.n_philos + 1);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table->ability.n_philos)
	{
		philos[i] = new_philo(i + 1, forks[i], forks[(i + 1) % table->ability.n_philos], table);
		if (philos[i] == NULL || forks[i] == NULL)
		{
			delete_philos(philos);
			delete_forks(forks);
			delete_table(table);
			return (NULL);
		}
		i++;
	}
	philos[table->ability.n_philos] = NULL;
	return (philos);
}

