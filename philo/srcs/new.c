/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:34 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 15:01:09 by hsawamur         ###   ########.fr       */
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
	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (NULL);
	}
	fork->fork = mutex;
	fork->is_used = false;
	return (fork);
}

t_philo	*new_philo(size_t id, t_fork *left, t_fork *right, t_philo_ability ability)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = id;
	philo->left_fork = left;
	philo->right_fork = right;
	philo->ability = ability;
	return (philo);
}

static t_philo_ability	new_philo_ability(int argc, char **argv)
{
	t_philo_ability	philo_ability;

	philo_ability.die_time = atoi(argv[2]);
	philo_ability.eat_time = atoi(argv[3]);
	philo_ability.sleep_time = atoi(argv[4]);
	if (argc == 5)
		philo_ability.eat_count = -1;
	else
		philo_ability.eat_count = atoi(argv[5]);
	return (philo_ability);
}

t_table	*new_table(int argc, char **argv)
{
	t_table			*table;
	t_philo_ability	philo_ability;
	int				size;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	printf("argc %d, argv %s %s %s %s %s\n",argc, argv[0], argv[1], argv[2], argv[3], argv[4]);
	size = atoi(argv[1]);
	printf("size %d\n", size);
	table->forks = create_forks(size);
	if (table->forks == NULL || table->forks[0] == NULL)
		return (NULL);
	philo_ability = new_philo_ability(argc, argv);
	table->philos = create_philos(table->forks, size, philo_ability);
	if (table->forks == NULL || table->philos[0] == NULL)
		return (NULL);
	return (table);
}
