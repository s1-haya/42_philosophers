/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:49:15 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 15:03:50 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thinking(t_philo *philo)
{
	print_info(philo, MESSAGE_THINKING);
	// printf("philo id: %d, last_eat_id: %d\n", philo->id, read_last_eat_philo_id(philo->left));
	// printf("philo id: %d, last_eat_id: %d\n", philo->id, read_last_eat_philo_id(philo->right));
	while ((philo->id == read_last_eat_philo_id(philo->left)
		|| philo->id == read_last_eat_philo_id(philo->right))
		&& !read_is_dead(philo->table))
	{
		usleep(100);
	}
	return (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count)
		|| check_philo_died(philo) || read_is_error(philo->table));
}
