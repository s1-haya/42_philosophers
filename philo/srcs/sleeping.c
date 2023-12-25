/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/25 16:18:45 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	sleeping(t_philo *philo)
{
	if (philo->id == read_last_eat_philo_id(philo->left)
		&& philo->id == read_last_eat_philo_id(philo->right))
	{
		print_info(philo, MESSAGE_SLEEPING);
		usleep(philo->table->ability.sleep_time * 1000);
	}
	return (false);
}
