/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:50:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/24 15:51:22 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MESSAGE_TAKEN_A_FORK "%d %ld has taken a fork\n"
# define MESSAGE_EATING "%d %ld is eating\n"
# define MESSAGE_SLEEPING "%d %ld is sleeping\n"
# define MESSAGE_THINKING "%d %ld is thinking\n"
# define MESSAGE_DIED "%d %ld died\n"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// enum philo_status {
// 	DEFAULT,
// 	EATING,
// 	SLPEENG,
// 	THINKING,
// 	DIED
// }

// typedef enum e_error_mes {
	
// }	t_error_mes;

typedef struct e_philo_ability {
	int		n_philos;
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
	bool			is_dead;
	bool			is_error;
	struct e_fork	*left;
	struct e_fork	*right;
	t_philo_ability	ability;
	long			birth_time;
	long			last_eat_time;
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
t_philo_ability	new_philo_ability(int argc, char **argv);
t_philo			**create_philos(t_philo_ability ability);
t_fork			**create_forks(int n_philo);
void			create_pthread(t_philo **philos);

long			get_ms();
long			get_elapsed_ms(long start_ms);
void			dying_message(t_philo *philo);
void			eating(t_philo *philo);

// delete.c
void			delete_table(t_table *table);
void			delete_forks(t_fork **forks);
void			delete_philos(t_philo **philos);
void			delete_pthread(t_philo **philo);

int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
#endif
