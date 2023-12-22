/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:41 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/22 18:21:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

#define ERROR_MES_CREATE_THREAD "pthread fail"

long get_usec()
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

long get_elapsed_ms(long start_usec)
{
	if (get_usec() == -1)
		return (-1);
	return ((get_usec() - start_usec) / 1000);
}

void print_info(t_philo *philo, char *mes)
{

	pthread_mutex_lock(&(philo->table->mes));
	if (!(read_is_dead(philo->table)|| read_is_error(philo->table)))
		printf(mes, get_elapsed_ms(read_start_time(philo->table)), philo->id);
	pthread_mutex_unlock(&(philo->table->mes));
}

void *test_pthread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!read_is_success(philo->table))
	{
		if (read_is_error(philo->table))
			return (NULL);
		usleep(100);
	}
	philo->last_eat_time = philo->table->start_time;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (check_philo_died(philo))
			break;
	}
	return (philo);
}

void create_pthread(t_philo **philos)
{
	int i;
	int p_create;
	long	start_time;

	i = 0;
	while (philos[i] != NULL)
	{
		p_create = pthread_create(&philos[i]->living, NULL, test_pthread, philos[i]);
		// printf("id: %d, n_philos: %d\n", i, philos[i]->ability.n_philos);
		if (p_create != 0)
		{
			write(2, ERROR_MES_CREATE_THREAD, ft_strlen(ERROR_MES_CREATE_THREAD));
			delete_pthread(philos, i);
			pthread_mutex_lock(&philos[i]->table->table);
			philos[i]->table->is_error = true;
			pthread_mutex_unlock(&philos[i]->table->table);
			return;
		}
		i++;
	}
	pthread_mutex_lock(&philos[0]->table->table);
	start_time = get_usec();
	philos[0]->table->start_time = start_time;
	philos[0]->table->is_success = true;
	pthread_mutex_unlock(&philos[0]->table->table);
}

t_fork **create_forks(int n_philos)
{
	t_fork **forks;
	int i;

	forks = malloc(sizeof(t_fork) * (n_philos + 1));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		forks[i] = new_fork();
		if (forks[i] == NULL)
		{
			delete_forks(forks);
			return (NULL);
		}
		if (i % 2 == 0)
			forks[i]->last_eat_philo = i + 1;
		else
			forks[i]->last_eat_philo = i + 2;
		i++;
	}
	if (i % 2 != 0)
		forks[i - 1]->last_eat_philo = i;
	forks[n_philos] = NULL;
	return (forks);
}

t_philo **create_philos(t_philo_ability ability)
{
	t_philo **philos;
	t_fork **forks;
	t_table *table;
	int i;

	philos = malloc(sizeof(t_philo) * ability.n_philos + 1);
	forks = create_forks(ability.n_philos);
	table = new_table(ability);
	if (philos == NULL || forks == NULL || table == NULL)
		return (NULL);
	i = 0;
	while (i < ability.n_philos)
	{
		philos[i] = new_philo(i + 1, forks[i], forks[(i + 1) % ability.n_philos], table);
		if (philos[i] == NULL || forks[i] == NULL)
		{
			delete_philos(philos);
			delete_forks(forks);
			delete_table(table);
			return (NULL);
		}
		i++;
	}
	philos[ability.n_philos] = NULL;
	return (philos);
}
