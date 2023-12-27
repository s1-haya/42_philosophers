/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:49:15 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 20:23:19 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

# define MESSAGE_THINKING "%ld %d is thinking\n"

bool	thinking(t_philo *philo)
{
	print_info(philo, MESSAGE_THINKING);
	while ((philo->id == get_last_eat_philo_id(philo->left)
			|| philo->id == get_last_eat_philo_id(philo->right))
		&& !get_is_dead(philo->table))
		usleep(300);
	return (false);
}
