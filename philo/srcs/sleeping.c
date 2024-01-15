/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/15 18:53:18 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#define MESSAGE_SLEEPING "%ld %d is sleeping\n"

void	perform_sleep(t_philo *philo)
{
	if (philo->id == get_last_eat_philo_id(philo->left)
		&& philo->id == get_last_eat_philo_id(philo->right))
	{
		print_info(philo, MESSAGE_SLEEPING);
		test_usleep(philo, philo->table->config.sleep_time * 1000);
	}
}
