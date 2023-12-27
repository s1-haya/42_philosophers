/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:45:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 17:46:02 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_last_eat_philo_id(t_fork *fork)
{
	int	id;

	id = 0;
	pthread_mutex_lock(&fork->fork);
	id = fork->last_eat_philo;
	pthread_mutex_unlock(&fork->fork);
	return (id);
}

bool	get_is_dead(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->read);
	read = table->is_dead;
	pthread_mutex_unlock(&table->read);
	return (read);
}

bool	get_is_success(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->read);
	read = table->is_success;
	pthread_mutex_unlock(&table->read);
	return (read);
}

bool	get_is_error(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->read);
	read = table->is_error;
	pthread_mutex_unlock(&table->read);
	return (read);
}

long	get_start_time(t_table *table)
{
	long	start_time;

	start_time = 0;
	pthread_mutex_lock(&table->read);
	start_time = table->start_time;
	pthread_mutex_unlock(&table->read);
	return (start_time);
}