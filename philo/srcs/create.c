/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/30 20:47:00 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

#define ERROR_MES_CREATE_THREAD "pthread fail"

long	get_usec()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

long	get_elapsed_ms(long start_usec)
{
	if (get_usec() == -1)
		return (-1);
	return ((get_usec() - start_usec) / 1000);
}

void	print_info(t_philo *philo, char *mes)
{

	if (pthread_mutex_lock(&(philo->mes)) != 0){
		perror("pthread_mutex_lock");
		exit(0);
	}
	if (!(philo->table->is_dead || philo->table->is_error))
		printf(mes, get_elapsed_ms(philo->table->start_time), philo->id);
	if (pthread_mutex_unlock(&(philo->mes)) != 0) {                                      
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
		// printf("last_eat_time %ld\n", philo->table->start_time);
		if (eating(philo) || sleeping(philo) || thinking(philo))
			break ;
	}
	return (philo);
}

void	create_pthread(t_philo **philos)
{
	int				i;
	int				p_create;
	long			start_time;
	t_table			*table;

	start_time = get_usec();
	table = new_table();
	i = 0;
	while (philos[i] != NULL)
	{
		philos[i]->table = table;
		philos[i]->last_eat_time = start_time;
		// printf("last_eat_time %ld\n", start_time);
		philos[i]->table->start_time = start_time;
		// printf("last_eat_time %ld\n", philos[i]->table->start_time);
		p_create = pthread_create(&philos[i]->living, NULL, test_pthread, philos[i]);
		// printf("id: %d, n_philos: %d\n", i, philos[i]->ability.n_philos);
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
	int				i;

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
