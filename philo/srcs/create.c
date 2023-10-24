/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/24 15:56:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

#define ERROR_MES_CREATE_THREAD "pthread fail"

long	get_ms()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec + tv.tv_usec / 1000);
}

long	get_elapsed_ms(long start_ms)
{
	return (get_ms() - start_ms);
}

void	print_info(t_philo *philo, char *mes)
{

	if (pthread_mutex_lock(&(philo->right->fork)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	printf(mes, get_elapsed_ms(philo->birth_time), philo->id);
	if (pthread_mutex_unlock(&(philo->right->fork)) != 0) {                                      
		perror("pthread_mutex_unlock() error");                                     
		exit(0);                                                                    
	}
}


void	*test_pthread(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo);
		usleep(philo->ability.sleep_time * 1000);
		// sleeping(philo);
		// thinking(philo);
		if (philo->is_dead || philo->is_error)
			dying_message(philo);
	}
	return (philo);
}

void	create_pthread(t_philo **philos)
{
	int				i;
	int				p_create;
	long			starting_time;

	starting_time = get_ms();
	i = 0;
	while (philos[i] != NULL)
	{
		philos[i]->birth_time = starting_time;
		philos[i]->last_eat_time = starting_time;
		p_create = pthread_create(&philos[i]->living, NULL, test_pthread, philos[i]);
		printf("id: %d, n_philos: %d\n", i, philos[i]->ability.n_philos);
		if (p_create != 0)
		{
			write(2, ERROR_MES_CREATE_THREAD, ft_strlen(ERROR_MES_CREATE_THREAD));
			return ;
		}
		i++;
	}
}

t_fork	**create_forks(int n_philos)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork) * (n_philos + 1));
	i = 0;
	while (i < n_philos)
	{
		forks[i] = new_fork();
		if (forks[i] == NULL)
		{
			delete_forks(forks);
			return (NULL);
		}
		i++;
	}
	forks[n_philos] = NULL;
	return (forks);
}

t_philo	**create_philos(t_philo_ability ability)
{
	t_philo			**philos;
	t_fork			**forks;
	int		i;

	philos = malloc(sizeof(t_philo) * ability.n_philos + 1);
	forks = create_forks(ability.n_philos);
	if (philos == NULL || forks == NULL)
		return (NULL);
	i = 0;
	while (i < ability.n_philos)
	{
		philos[i] = new_philo(i, forks[i], forks[(i + 1) % ability.n_philos], ability);
		if (forks[i] == NULL)
		{
			delete_philos(philos);
			return (NULL);
		}
		i++;
	}
	philos[ability.n_philos] = NULL;
	return (philos);
}
