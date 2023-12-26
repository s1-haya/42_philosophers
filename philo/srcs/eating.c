/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/26 13:07:20 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_eat(t_philo *philo)
{
	philo->last_eat_time = get_usec();
	p_usleep(philo->table->ability.eat_time * 1000);
	if (philo->table->ability.eat_count != -1)
	{
		if (read_is_dead(philo->table))
			return ;
		pthread_mutex_lock(&(philo->table->read));
		philo->n_ate++;
		if (philo->table->n_philos_ate >= philo->n_ate)
			philo->table->n_philos_ate-- ;
		philo->table->is_dead = philo->table->n_philos_ate == 0;
		pthread_mutex_unlock(&(philo->table->read));
	}
}

bool	eating(t_philo *philo)
{
	if ((philo->id == read_last_eat_philo_id(philo->left)
			|| philo->id == read_last_eat_philo_id(philo->right)))
		return (false);
	print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
	print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
	print_info(philo, MESSAGE_EATING);
	time_to_eat(philo);
	pthread_mutex_lock(&(philo->left->fork));
	philo->left->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->left->fork));
	pthread_mutex_lock(&(philo->right->fork));
	philo->right->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->right->fork));
	return (false);
}
