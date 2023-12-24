/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:52:18 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/21 21:13:50 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_last_eat_philo_id(t_fork *fork)
{
	int	id;

	id = 0;
	pthread_mutex_lock(&fork->fork);
	id = fork->last_eat_philo;
	pthread_mutex_unlock(&fork->fork);
	return (id);
}

bool	read_is_dead(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->table);
	read = table->is_dead;
	pthread_mutex_unlock(&table->table);
	return (read);
}

bool	read_is_success(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->table);
	read = table->is_success;
	pthread_mutex_unlock(&table->table);
	return (read);
}

bool	read_is_error(t_table *table)
{
	bool	read;

	read = false;
	pthread_mutex_lock(&table->table);
	read = table->is_error;
	pthread_mutex_unlock(&table->table);
	return (read);
}

long	read_start_time(t_table *table)
{
	long	start_time;

	start_time = 0;
	pthread_mutex_lock(&table->table);
	start_time = table->start_time;
	pthread_mutex_unlock(&table->table);
	return (start_time);
}
