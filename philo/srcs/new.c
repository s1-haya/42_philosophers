/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:34 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/21 18:28:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*new_fork()
{
	t_fork			*fork;
	pthread_mutex_t	mutex;
	
	fork = malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	if (pthread_mutex_init(&mutex, NULL))
		return (NULL);
	fork->fork = mutex;
	fork->is_used = false;
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
	philo->is_eat = false;
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
	pthread_mutex_t	data;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->n_philos_ate = 0;
	table->is_success = false;
	table->is_error = false;
	table->is_dead = false;
	if (pthread_mutex_init(&mes, NULL))
		return (NULL);
	table->mes = mes;
	if (pthread_mutex_init(&data, NULL))
		return (NULL);
	table->table = data;
	table->ability = ability;
	return (table);
}
