/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/06 16:11:48 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_error(int argc, char **argv);

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

t_philo_ability	new_philo_ability(int argc, char **argv)
{
	t_philo_ability	philo_ability;

	philo_ability.die_time = atoi(argv[2]);
	philo_ability.eat_time = atoi(argv[3]);
	philo_ability.sleep_time = atoi(argv[4]);
	if (argc == 4)
		philo_ability.eat_count = -1;
	else
		philo_ability.eat_count = atoi(argv[5]);
	return (philo_ability);
}

t_philo	**create_philos(t_fork **forks, size_t size, t_philo_ability ability)
{
	t_philo	**philos;
	size_t	i;

	philos = malloc(sizeof(t_philo) * size + 1);
	i = 0;
	while (i < size)
	{
		philos[i] = new_philo(i, forks[i], forks[(i + 1) % size], ability);
		i++;
	}
	return (philos);
}

t_fork	**create_forks(size_t size)
{
	t_fork	**forks;
	size_t	i;

	forks = malloc(sizeof(t_fork) * size + 1);
	i = 0;
	while (i < size)
	{
		forks[i] = new_fork();
		i++;
	}
	forks[size] = NULL;
	return (forks);
}

t_table	*new_table(int argc, char **argv)
{
	t_table			*table;
	t_philo_ability	philo_ability;
	size_t	size;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	exit(0);
	size = atoi(argv[1]);
	table->forks = create_forks(size);
	if (table->forks == NULL)
		return (NULL);
	philo_ability = new_philo_ability(argc, argv);
	table->philos = create_philos(table->forks, size, philo_ability);
	if (table->philos == NULL)
		return (NULL);
	return (table);
}

void	init(t_table *table, int argc, char **argv)
{
	// if (is_error(argc, argv))
	// 	table = NULL;
	// else
	table = new_table(argc, argv);
}

// void	exec(t_table *table)
// {
// 	create_pthread(table);
// }

// void	free_table(t_table *table)
// {
// 	delete_pthread(table);
// }

int main(int argc, char **argv)
{
	t_table	table;

	printf("argv %s %s\n",argv[0], argv[1]);
	init(&table, argc, argv);
	// exit(0);
	// printf_debug_table(table);
	// exec(table);
	// free_table(table);
	return (0);
}
