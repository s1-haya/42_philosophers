/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 15:03:41 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleeping(t_philo *philo)
{
	if (philo->id == read_last_eat_philo_id(philo->left)
		&& philo->id == read_last_eat_philo_id(philo->right))
	{
		print_info(philo, MESSAGE_SLEEPING);
		p_usleep(philo->table->ability.sleep_time * 1000);
	}
	return (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo) || read_is_error(philo->table));
}
