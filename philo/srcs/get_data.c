/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:45:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 18:17:08 by hsawamur         ###   ########.fr       */
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
	bool	get_data;

	get_data = false;
	pthread_mutex_lock(&table->get_data);
	get_data = table->is_dead;
	pthread_mutex_unlock(&table->get_data);
	return (get_data);
}

bool	get_is_success(t_table *table)
{
	bool	get_data;

	get_data = false;
	pthread_mutex_lock(&table->get_data);
	get_data = table->is_success;
	pthread_mutex_unlock(&table->get_data);
	return (get_data);
}

bool	get_is_error(t_table *table)
{
	bool	get_data;

	get_data = false;
	pthread_mutex_lock(&table->get_data);
	get_data = table->is_error;
	pthread_mutex_unlock(&table->get_data);
	return (get_data);
}

long	get_start_time(t_table *table)
{
	long	start_time;

	start_time = 0;
	pthread_mutex_lock(&table->get_data);
	start_time = table->start_time;
	pthread_mutex_unlock(&table->get_data);
	return (start_time);
}