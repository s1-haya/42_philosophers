/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:50:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/09 15:55:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MESSAGE_TAKEN_A_FORK "timestamp_in_ms X has taken a fork"
# define MESSAGE_EATING "timestamp_in_ms X is eating"
# define MESSAGE_SLEEPING "timestamp_in_ms X is sleeping"
# define MESSAGE_THINKING "timestamp_in_ms X is thinking"
# define MESSAGE_DIED "timestamp_in_ms X died"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

// enum philo_status {
// 	DEFAULT,
// 	EATING,
// 	SLPEENG,
// 	THINKING,
// 	DIED
// }

typedef struct e_philo_ability {
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_count;
}	t_philo_ability;

typedef struct e_fork {
	pthread_mutex_t	fork;
	bool			is_used;
}	t_fork;

typedef struct e_philo {
	int				id;
	pthread_t		living;
	struct e_fork	*left_fork;
	struct e_fork	*right_fork;
	t_philo_ability	ability;
	long			time_of_birth;
}	t_philo;

typedef struct e_table {
	t_fork		**forks;
	t_philo		**philos;
	long		starting_time;
}	t_table;

void	printf_debug_table(t_table *table);

// new.c
t_table	*new_table(int argc, char **argv, int n_philo);
t_philo	*new_philo(size_t id, t_fork *left, t_fork *right, t_philo_ability ability);
t_fork	*new_fork();

// create.c
t_philo	**create_philos(t_fork **forks, int n_philo, t_philo_ability ability);
t_fork	**create_forks(int n_philo);

// delete.c
void	delete_table(t_table *table);
#endif
