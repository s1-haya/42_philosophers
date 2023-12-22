/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 15:03:28 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool check_philo_ate(int n_philos_ate, int eat_count)
{
	if (eat_count == -1)
		return (false);
	return (n_philos_ate >= eat_count);
}

void	time_to_eat(t_philo *philo)
{	
	if (philo->table->ability.eat_count != -1 && !philo->is_eat)
	{
		philo->is_eat = true;
		pthread_mutex_lock(&(philo->table->table));
		philo->table->n_philos_ate++;
		printf("n_ate: expect %d, real %d\n", philo->table->ability.eat_count, philo->table->n_philos_ate);
		pthread_mutex_unlock(&(philo->table->table));
	}
	philo->last_eat_time = get_usec();
	p_usleep(philo->table->ability.eat_time * 1000);
}

bool	eating(t_philo *philo)
{
	if (philo->id == read_last_eat_philo_id(philo->left)
		|| philo->id == read_last_eat_philo_id(philo->right))
		return (false);
	print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
	print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
	print_info(philo, MESSAGE_EATING);
	time_to_eat(philo);
	pthread_mutex_lock(&(philo->left->fork));
	philo->left->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->left->fork));
	pthread_mutex_lock(&(philo->right->fork));
	philo->right->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->right->fork));
	return (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo) || read_is_error(philo->table));
}
