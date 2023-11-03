/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:52:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/03 17:00:26 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_died(t_philo *philo)
{
	if (get_elapsed_ms(philo->last_eat_time) >= philo->table->ability.die_time)
	{
		if (pthread_mutex_lock(&(philo->table->mes)) != 0){
			perror("pthread_mutex_lock");
			exit(0);
		}
		if (!philo->table->is_dead)
			dying_message(philo);
		philo->table->is_dead = true;
		if (pthread_mutex_unlock(&(philo->table->mes)) != 0) {                                      
			perror("pthread_mutex_unlock() error");                                     
			exit(0);                                                                    
		}
		return (true);
	}
	return (false);
}
void	dying_message(t_philo *philo)
{
	printf(MESSAGE_DIED, get_elapsed_ms(philo->table->start_time), philo->id);
}
