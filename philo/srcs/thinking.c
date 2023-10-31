/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:49:15 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/30 19:00:02 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thinking(t_philo *philo)
{
	if (check_philo_ate(philo->table->n_philos_ate, philo->ability.eat_count)
		|| check_philo_died(philo) || philo->table->is_error)
		return (true);
	print_info(philo, MESSAGE_THINKING);
	return (check_philo_died(philo));
}
