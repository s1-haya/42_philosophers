/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_usleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:52:34 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 18:26:20 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_usleep(int end_time)
{
	long	start_time;

	start_time = get_usec();
	while (end_time > (get_usec() - start_time))
		usleep(300);
}
