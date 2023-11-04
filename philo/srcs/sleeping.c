/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/04 16:22:30 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleeping(t_philo *philo)
{
	if (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count)
		|| check_philo_died(philo) || philo->table->is_error)
		return (true);
	if (philo->id == philo->left->last_eat_philo
		&& philo->id == philo->right->last_eat_philo)
	{
		pthread_mutex_lock(&(philo->right->fork));
		pthread_mutex_lock(&(philo->left->fork));
		print_info(philo, MESSAGE_SLEEPING);
		philo->right->is_used = false;
		philo->left->is_used = false;
		p_usleep(philo->table->ability.sleep_time * 1000);
		pthread_mutex_unlock(&(philo->right->fork));
		pthread_mutex_unlock(&(philo->left->fork));
	}
	return (false);
}
