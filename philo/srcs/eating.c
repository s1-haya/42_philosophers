/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/06 16:03:07 by hsawamur         ###   ########.fr       */
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
		pthread_mutex_lock(&(philo->table->n_eat_log));
		philo->table->n_philos_ate++;
		printf("n_ate: expect %d, real %d\n", philo->table->ability.eat_count, philo->table->n_philos_ate);
		pthread_mutex_unlock(&(philo->table->n_eat_log));
	}
	philo->last_eat_time = get_usec();
	p_usleep(philo->table->ability.eat_time * 1000);
}

bool eating(t_philo *philo)
{
	if (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo) || philo->table->is_error)
		return (true);
	// printf("philo id: %d\n", philo->id);
	// printf("philo left id: %d\n", philo->left->last_eat_philo);
	// printf("philo right id: %d\n", philo->right->last_eat_philo);
	if (philo->id == philo->left->last_eat_philo
		|| philo->id == philo->right->last_eat_philo)
		return (false);
	print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
	print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
	print_info(philo, MESSAGE_EATING);
	time_to_eat(philo);
	pthread_mutex_lock(&(philo->left->fork));
	philo->left->is_used = true;
	philo->left->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->left->fork));
	pthread_mutex_lock(&(philo->right->fork));
	philo->right->is_used = true;
	philo->right->last_eat_philo = philo->id;
	pthread_mutex_unlock(&(philo->right->fork));
	// printf("philo id: %d\n", philo->id);
	// printf("philo left id: %d\n", philo->left->last_eat_philo);
	// printf("philo right id: %d\n", philo->right->last_eat_philo);
	return (false);
}
