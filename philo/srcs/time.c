/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:05:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/25 16:19:30 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

long	get_usec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

long	get_elapsed_ms(long start_usec)
{
	if (get_usec() == -1)
		return (-1);
	return ((get_usec() - start_usec) / 1000);
}

void	p_usleep(int end_time)
{
	long	start_time;

	start_time = get_usec();
	while (end_time > (get_usec() - start_time))
		usleep(300);
}
