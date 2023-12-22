/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:49:15 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 18:19:53 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thinking(t_philo *philo)
{
	print_info(philo, MESSAGE_THINKING);
	while ((philo->id == read_last_eat_philo_id(philo->left)
		|| philo->id == read_last_eat_philo_id(philo->right))
		&& !read_is_dead(philo->table))
		usleep(300);
	return (false);
}
