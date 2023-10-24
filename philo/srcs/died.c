/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:52:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/24 09:24:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	check_philo_died();
void	dying_message(t_philo *philo)
{
	printf(MESSAGE_DIED, philo->id, get_elapsed_ms(philo->birth_time));
}
