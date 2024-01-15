/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:05:38 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/15 18:54:05 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	get_usec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

long	get_elapsed_ms(long start_usec)
{
	long	usec;

	usec = get_usec();
	if (usec == -1)
		return (-1);
	return ((usec - start_usec) / 1000);
}

void	p_usleep(long end_time)
{
	long	start_time;

	start_time = get_usec();
	while (end_time > (get_usec() - start_time))
		usleep(300);
}

// #include <stdio.h>
void	test_usleep(t_philo *philo, long end_time)
{
	long	start_time;

	start_time = get_usec();
	while (end_time > (get_usec() - start_time))
	{
		check_philo_died(philo);
		usleep(200);
	}
}
