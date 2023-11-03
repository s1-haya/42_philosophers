/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/03 16:59:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void try_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		perror("pthread_mutex_lock");
		exit(0);
	}
}

void try_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		perror("pthread_mutex_unlock() error");
		exit(0);
	}
}

bool check_philo_ate(int n_philos_ate, int eat_count)
{
	if (eat_count == -1)
		return (false);
	return (n_philos_ate >= eat_count);
}

bool time_to_eat(t_philo *philo)
{
	bool flag;

	flag = false;
	if (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo))
		return (true);
	if (philo->table->ability.eat_count != -1 && !philo->is_eat)
	{
		philo->is_eat = true;
		pthread_mutex_lock(&(philo->table->n_eat_log));
		philo->table->n_philos_ate++;
		printf("n_ate: expect %d, real %d\n", philo->table->ability.eat_count, philo->table->n_philos_ate);
		pthread_mutex_unlock(&(philo->table->n_eat_log));
	}
	print_info(philo, MESSAGE_EATING);
	p_usleep(philo->table->ability.eat_time * 1000);
	if (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo))
		return (true);
	philo->last_eat_time = get_usec();
	return (flag);
	// printf("last_eat_time %ld\n", philo->table->start_time);
	// printf("last_eat_time %ld\n", get_usec());
	// printf("last_eat_time %ld\n", get_elapsed_ms(philo->last_eat_time));
	// printf("die_time       %d\n", philo->table->ability.die_time);
	// printf("eat_count      %d\n", philo->table->ability.eat_count);
}

bool eating(t_philo *philo)
{
	int counter;

	counter = 0;
	while (counter != 2)
	{
		if (philo->id % 2 == 0)
		{
			if (pthread_mutex_lock(&(philo->left->fork)) != 0)
			{
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) && !philo->left->is_used && (!philo->table->is_dead))
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
				philo->left->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->left->fork)) != 0)
			{
				perror("pthread_mutex_unlock() error");
				exit(0);
			}
			if (pthread_mutex_lock(&(philo->right->fork)) != 0)
			{
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) && !philo->right->is_used && (!philo->table->is_dead))
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
				philo->right->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->right->fork)) != 0)
			{
				perror("pthread_mutex_unlock() error");
				exit(0);
			}
		}
		else
		{
			if (pthread_mutex_lock(&(philo->right->fork)) != 0)
			{
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) && !philo->right->is_used && (!philo->table->is_dead))
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_RIGHT);
				philo->right->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->right->fork)) != 0)
			{
				perror("pthread_mutex_unlock() error");
				exit(0);
			}
			if (pthread_mutex_lock(&(philo->left->fork)) != 0)
			{
				perror("pthread_mutex_lock");
				exit(0);
			}
			if (!check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) && !philo->left->is_used && (!philo->table->is_dead))
			{
				print_info(philo, MESSAGE_TAKEN_A_FORK_LEFT);
				philo->left->is_used = true;
				counter++;
			}
			if (pthread_mutex_unlock(&(philo->left->fork)) != 0)
			{
				perror("pthread_mutex_unlock() error");
				exit(0);
			}
		}
		if (check_philo_ate(philo->table->n_philos_ate, philo->table->ability.eat_count) || check_philo_died(philo) || philo->table->is_error)
			return (true);
	}
	return (time_to_eat(philo));
}
