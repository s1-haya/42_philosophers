/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:34 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/26 12:23:09 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*new_fork(void)
{
	t_fork			*fork;
	pthread_mutex_t	mutex;

	if (pthread_mutex_init(&mutex, NULL))
		return (NULL);
	fork = malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	fork->fork = mutex;
	return (fork);
}

t_philo	*new_philo(size_t id, t_fork *left, t_fork *right, t_table *table)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = id;
	philo->left = left;
	philo->right = right;
	philo->n_ate = 0;
	philo->table = table;
	return (philo);
}

t_philo_ability	new_philo_ability(int argc, char **argv)
{
	t_philo_ability	philo_ability;

	philo_ability.n_philos = atoi(argv[1]);
	philo_ability.die_time = atoi(argv[2]);
	philo_ability.eat_time = atoi(argv[3]);
	philo_ability.sleep_time = atoi(argv[4]);
	if (argc == 5)
		philo_ability.eat_count = -1;
	else
		philo_ability.eat_count = atoi(argv[5]);
	return (philo_ability);
}

t_table	*new_table(t_philo_ability ability)
{
	t_table			*table;
	pthread_mutex_t	mes;
	pthread_mutex_t	read;

	if (pthread_mutex_init(&mes, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&read, NULL) != 0)
	{
		pthread_mutex_destroy(&mes);
		return (NULL);
	}
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->n_philos_ate = ability.n_philos;
	table->is_success = false;
	table->is_error = false;
	table->is_dead = false;
	table->mes = mes;
	table->read = read;
	table->ability = ability;
	return (table);
}
