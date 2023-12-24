/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:21:32 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/23 16:38:59 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, char *mes)
{
	pthread_mutex_lock(&(philo->table->mes));
	if (!(read_is_dead(philo->table)|| read_is_error(philo->table)))
		printf(mes, get_elapsed_ms(read_start_time(philo->table)), philo->id);
	pthread_mutex_unlock(&(philo->table->mes));
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!read_is_success(philo->table))
	{
		if (read_is_error(philo->table))
			return (NULL);
		usleep(100);
	}
	philo->last_eat_time = philo->table->start_time;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (check_philo_died(philo))
			break;
	}
	return (philo);
}

int	start_simulation(t_philo **philos)
{
	long	start_time;
	int		index;

	index = create_pthread(philos);
	if (index == philos[0]->table->ability.n_philos)
	{
		pthread_mutex_lock(&philos[0]->table->table);
		start_time = get_usec();
		philos[0]->table->start_time = start_time;
		philos[0]->table->is_success = true;
		pthread_mutex_unlock(&philos[0]->table->table);
	}
	return (index);
}

int	end_simulation(t_philo **philos, int index)
{
	int		i;
	char	*ret;

	i = 0;
	while (i < index)
	{
		pthread_join(philos[i]->living, (void **)&ret);
		i++;
	}
	delete_philos(philos);
	if (index != philos[0]->table->ability.n_philos)
		return (ERROR);
	return (SUCCESS);
}
