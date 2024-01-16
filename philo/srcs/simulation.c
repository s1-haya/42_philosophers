/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:21:32 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/16 14:51:54 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	print_info(t_philo *philo, char *print_message)
{
	pthread_mutex_lock(&(philo->table->print_message));
	if (!(get_is_dead(philo->table) || get_is_error(philo->table)))
		printf(print_message,
			get_elapsed_ms(get_start_time(philo->table)),
			philo->id);
	pthread_mutex_unlock(&(philo->table->print_message));
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_is_success(philo->table))
	{
		if (get_is_error(philo->table))
			return (NULL);
		usleep(100);
	}
	philo->last_eat_time = philo->table->start_time;
	while (!check_philo_died(philo))
	{
		perform_eat(philo);
		perform_sleep(philo);
		perform_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo **philos)
{
	long	start_time;
	int		index;

	index = create_pthread(philos);
	if (index == philos[0]->table->config.n_philos)
	{
		pthread_mutex_lock(&philos[0]->table->get_data);
		start_time = get_usec();
		philos[0]->table->start_time = start_time;
		philos[0]->table->is_success = true;
		pthread_mutex_unlock(&philos[0]->table->get_data);
	}
	return (index);
}

int	end_simulation(t_philo **philos, int index)
{
	int		i;
	int		status;

	i = 0;
	status = index != philos[0]->table->config.n_philos;
	while (i < index)
	{
		pthread_join(philos[i]->living, NULL);
		i++;
	}
	delete_philos(philos, index);
	delete_table(philos[i]->table);
	return (status);
}
