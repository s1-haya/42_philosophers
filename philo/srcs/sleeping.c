/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/27 14:54:59 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	if (!(philo->right->is_used && philo->left->is_used))
		return ;
	philo->right->is_used = false;
	philo->left->is_used = false;
	print_info(philo, MESSAGE_SLEEPING);
}
