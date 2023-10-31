/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/31 16:17:33 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleeping(t_philo *philo)
{
	if (check_philo_ate(philo->table->n_philos_ate, philo->ability.eat_count)
		|| check_philo_died(philo) || philo->table->is_error)
		return (true);
	if (!(philo->right->is_used && philo->left->is_used))
		return (false);
	if (pthread_mutex_lock(&(philo->right->fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	philo->right->is_used = false;
	if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {
		perror("pthread_mutex_unlock() error");
		exit(0);
	}
	if (pthread_mutex_lock(&(philo->left->fork)) != 0){
				perror("pthread_mutex_lock");
				exit(0);
			}
	philo->left->is_used = false;
	if (pthread_mutex_unlock(&(philo->left->fork)) != 0) {
		perror("pthread_mutex_unlock() error");
		exit(0);
	}
	print_info(philo, MESSAGE_SLEEPING);
	usleep(philo->ability.sleep_time * 1000);
	return (check_philo_ate(philo->table->n_philos_ate, philo->ability.eat_count)
		|| check_philo_died(philo));
}
