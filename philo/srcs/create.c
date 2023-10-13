/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/13 16:23:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

#define ERROR_MES_CREATE_THREAD "pthread fail"

void	*test_pthread(void *arg)
{
	t_philo	*data;
	struct timeval	tv;

	data = (t_philo *)arg;

	// printf("id %d\n", (*data).num);
	for (int i = 0; i < N_THREAD; i++){
		printf("id %d, time %ld\n", data->id, getMsTime(&tv) - data->time_of_birth);
		usleep(1000);
	}

	printf("waiting N %d...\n", data->id);
	if (pthread_mutex_lock(&(data->right.fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	printf("pthread N %d\n", data->id);
	if (pthread_mutex_unlock(&(data->right.fork)) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
	return (data);
}

void	create_pthread(t_table *table, int n_philo)
{
	struct timeval	tv;
	int				i;
	int				p_create;
	long			starting_time;

	starting_time = getMsTime(&tv);
	i = 0;
	while (i < n_philo)
	{
		table->philos[i]->time_of_birth = starting_time;
		p_create = pthread_create(&table->philos[i]->living, NULL, test_pthread, table->philos[i]);
		if (p_create != 0)
		{
			write(2, ERROR_MES_CREATE_THREAD, ft_strlen(ERROR_MES_CREATE_THREAD));
			return ;
		}
	}
}

t_philo	**create_philos(t_fork **forks, int n_philo, t_philo_ability ability)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * n_philo + 1);
	i = 0;
	while (i < n_philo)
	{
		philos[i] = new_philo(i, forks[i], forks[(i + 1) % n_philo], ability);
		i++;
	}
	philos[n_philo] = NULL;
	return (philos);
}

t_fork	**create_forks(int n_philo)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork) * (n_philo + 1));
	i = 0;
	while (i < n_philo)
	{
		forks[i] = new_fork();
		i++;
	}
	forks[n_philo] = NULL;
	return (forks);
}
