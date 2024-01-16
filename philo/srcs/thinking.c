/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:49:15 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/16 14:21:11 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#define MESSAGE_THINKING "%ld %d is thinking\n"

void	perform_think(t_philo *philo)
{
	print_info(philo, MESSAGE_THINKING);
	while ((philo->id == get_last_eat_philo_id(philo->left)
			|| philo->id == get_last_eat_philo_id(philo->right)))
	{
		if (check_philo_died(philo))
			break ;
		usleep(300);
	}
}
