/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/30 19:11:45 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
}

void	try_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
}

bool	check_philo_ate(int n_philos_ate, int eat_count)
{
	if (eat_count == -1)
		return (false);
	return (n_philos_ate >= eat_count);
}

bool	time_to_eat(t_philo *philo)
{
	print_info(philo, MESSAGE_EATING);
	usleep(philo->ability.eat_time * 1000);
	// printf("last_eat_time %ld\n", philo->table->start_time);
	// printf("last_eat_time %ld\n", get_usec());
	// printf("last_eat_time %ld\n", get_elapsed_ms(philo->last_eat_time));
	// printf("die_time       %d\n", philo->ability.die_time);
	if (check_philo_ate(philo->table->n_philos_ate, philo->ability.eat_count)
		|| check_philo_died(philo))
		return (true);
	philo->last_eat_time = get_usec();
	if (philo->ability.eat_count != -1 && !philo->is_eat)
	{
		philo->is_eat = true;
		philo->table->n_philos_ate ++;
	}
	return (false);
	// printf("eat_count      %d\n", philo->ability.eat_count);
}

bool	eating(t_philo *philo)
{
	// bool	flag;
	int	counter;

	// flag = true;
	// if (philo->right->is_used || philo->left->is_used
	// 	|| philo->table->is_dead || philo->table->is_error)
	// 	return ;
	// philo->table->is_dead = true;
	counter = 0;
	while (counter != 2)
	{
		if (check_philo_ate(philo->table->n_philos_ate, philo->ability.eat_count)
			|| check_philo_died(philo) || philo->table->is_error)
			return (true);
		if (philo->id % 2 == 0)
		{
			if (pthread_mutex_lock(&(philo->left->fork)) != 0){
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!philo->left->is_used)
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
				philo->left->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->left->fork)) != 0) {                                      
				perror("pthread_mutex_unlock() error");                                     
				exit(0);                                                                    
			}
			if (pthread_mutex_lock(&(philo->right->fork)) != 0){
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!philo->right->is_used)
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
				philo->right->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {                                      
				perror("pthread_mutex_unlock() error");                                     
				exit(0);                                                                    
			}
		}
		else
		{
			if (pthread_mutex_lock(&(philo->right->fork)) != 0){
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!philo->right->is_used)
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
				philo->right->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {                                      
				perror("pthread_mutex_unlock() error");                                     
				exit(0);                                                                    
			}
			if (pthread_mutex_lock(&(philo->left->fork)) != 0){
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!philo->left->is_used)
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
				philo->left->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->left->fork)) != 0) {                                      
				perror("pthread_mutex_unlock() error");                                     
				exit(0);                                                                    
			}
		}
	}
	return (time_to_eat(philo));
	// printf("pthread N %d\n", philo->id);
}
