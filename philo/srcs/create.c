/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 16:03:58 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	create_pthread()
// {
	// table->starting_time = getMsTime(&tv);
// 	for (int i = 0; i < N_THREAD; i++){
// 		data[i] = (t_num_pthread *)malloc(sizeof(t_num_pthread));
// 		data[i]->num = i;
// 		data[i]->ms_init = ms;
// 		data[i]->mutex = mutex;
// 		p_create = pthread_create(&v[i], NULL, test_pthread, data[i]);
// 		if (p_create != 0)
// 		{
// 			perror("pthread_create");
// 			return (0);
// 		}
// 	}
// }

t_philo	**create_philos(t_fork **forks, int n_philo, t_philo_ability ability)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * n_philo + 1);
	i = 0;
	while (i < n_philo)
	{
		philos[i] = new_philo(i, forks[i], forks[(i + 1) % n_philo], ability);
		i++;
	}
	philos[n_philo] = NULL;
	return (philos);
}

t_fork	**create_forks(int n_philo)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork) * (n_philo + 1));
	i = 0;
	while (i < n_philo)
	{
		forks[i] = new_fork();
		i++;
	}
	forks[n_philo] = NULL;
	return (forks);
}
