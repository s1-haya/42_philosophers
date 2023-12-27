/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:52:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 17:49:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_died(t_philo *philo)
{
	if (get_elapsed_ms(philo->last_eat_time) >= philo->table->ability.die_time
		|| philo->table->ability.n_philos == 1)
	{
		if (!get_is_dead(philo->table))
			dying_message(philo);
		return (true);
	}
	return (false);
}

void	dying_message(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->read));
	philo->table->is_dead = true;
	pthread_mutex_unlock(&(philo->table->read));
	pthread_mutex_lock(&(philo->table->mes));
	printf(MESSAGE_DIED, get_elapsed_ms(philo->table->start_time), philo->id);
	pthread_mutex_unlock(&(philo->table->mes));
}
