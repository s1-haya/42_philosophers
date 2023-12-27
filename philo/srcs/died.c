/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:52:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 20:23:32 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

# define MESSAGE_DIED "%ld %d died\n"

bool	check_philo_died(t_philo *philo)
{
	if (get_elapsed_ms(philo->last_eat_time) >= philo->table->config.die_time
		|| philo->table->config.n_philos == 1)
	{
		if (!get_is_dead(philo->table))
			dying_message(philo);
		return (true);
	}
	return (false);
}

void	dying_message(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->get_data));
	philo->table->is_dead = true;
	pthread_mutex_unlock(&(philo->table->get_data));
	pthread_mutex_lock(&(philo->table->print_message));
	printf(MESSAGE_DIED, get_elapsed_ms(philo->table->start_time), philo->id);
	pthread_mutex_unlock(&(philo->table->print_message));
}
