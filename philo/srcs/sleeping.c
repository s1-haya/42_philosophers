/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/06 16:20:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleeping(t_philo *philo)
{
	if (philo->id == philo->left->last_eat_philo
		&& philo->id == philo->right->last_eat_philo)
	{
		pthread_mutex_lock(&(philo->left->fork));
		philo->left->is_used = false;
		pthread_mutex_unlock(&(philo->left->fork));
		pthread_mutex_lock(&(philo->right->fork));
		philo->right->is_used = false;
		pthread_mutex_unlock(&(philo->right->fork));
		print_info(philo, MESSAGE_SLEEPING);
		p_usleep(philo->table->ability.sleep_time * 1000);
	}
	return (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo) || philo->table->is_error);
}
