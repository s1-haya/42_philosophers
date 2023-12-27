/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:34 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/27 20:22:21 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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

t_config	new_config(int argc, char **argv)
{
	t_config	config;

	config.n_philos = atoi(argv[1]);
	config.die_time = atoi(argv[2]);
	config.eat_time = atoi(argv[3]);
	config.sleep_time = atoi(argv[4]);
	if (argc == 5)
		config.eat_count = -1;
	else
		config.eat_count = atoi(argv[5]);
	return (config);
}

t_table	*new_table(t_config config)
{
	t_table			*table;
	pthread_mutex_t	print_message;
	pthread_mutex_t	get_data;

	if (pthread_mutex_init(&print_message, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&get_data, NULL) != 0)
	{
		pthread_mutex_destroy(&print_message);
		return (NULL);
	}
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->n_philos_ate = 0;
	table->is_success = false;
	table->is_error = false;
	table->is_dead = false;
	table->print_message = print_message;
	table->get_data = get_data;
	table->config = config;
	return (table);
}
