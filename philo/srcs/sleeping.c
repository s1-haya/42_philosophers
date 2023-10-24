/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:50:06 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/21 22:50:15 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	printf("waiting N %d...\n", philo->id);
	if (pthread_mutex_lock(&(philo->right->fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	printf("pthread N %d\n", philo->id);
	if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
}
