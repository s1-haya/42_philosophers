/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:47:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/24 09:49:27 by hsawamur         ###   ########.fr       */
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

void	time_to_eat(t_philo *philo)
{
	usleep(philo->ability.eat_time * 1000);
		// || philo->ability.eat_count )
	printf("last_eat_time %ld\n", get_elapsed_ms(philo->last_eat_time));
	printf("die_time       %d\n", philo->ability.die_time);
	if (get_elapsed_ms(philo->last_eat_time) >= philo->ability.die_time)
	{
		dying_message(philo);
		exit(1);	
	}
	philo->last_eat_time = get_ms();
	philo->ability.eat_count ++;
	printf("eat_count      %d\n", philo->ability.eat_count);
}

void	eating(t_philo *philo)
{
	// try_pthread_mutex_lock(philo);
	if (philo->left->is_used || philo->right->is_used)
		return ;
	printf("waiting N %d...\n", philo->id);
	time_to_eat(philo);
	if (pthread_mutex_lock(&(philo->right->fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	if (pthread_mutex_lock(&(philo->left->fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	// philo->left->is_used = true;
	// philo->right->is_used = true;
	//　時間はlockの外でやってstatusだけは中でやる。
	// そうすることによってstatusがはんていにな
	if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
	if (pthread_mutex_unlock(&(philo->left->fork)) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
	printf("pthread N %d\n", philo->id);
}
