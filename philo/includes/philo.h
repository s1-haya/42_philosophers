/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:50:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/31 15:34:43 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MESSAGE_TAKEN_A_FORK_RIGHT "%ld %d has taken a right fork\n"
# define MESSAGE_TAKEN_A_FORK_LEFT "%ld %d has taken a left fork\n"
# define MESSAGE_EATING "%ld %d is eating\n"
# define MESSAGE_SLEEPING "%ld %d is sleeping\n"
# define MESSAGE_THINKING "%ld %d is thinking\n"
# define MESSAGE_DIED "%ld %d died\n"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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


typedef struct e_table {
	int				n_philos_ate;
	bool			is_error;
	bool			is_dead;
	long			start_time;
	pthread_mutex_t	mes;
}	t_table;

typedef struct e_philo {
	int				id;
	pthread_t		living;
	struct e_fork	*left;
	struct e_fork	*right;
	t_philo_ability	ability;
	long			last_eat_time;
	bool			is_eat;
	struct e_table	*table;
}	t_philo;

void	printf_debug_table(t_table *table);

// new.c
t_table	*new_table();
t_philo	*new_philo(size_t id, t_fork *left, t_fork *right, t_philo_ability ability);
t_fork	*new_fork();

// create.c
t_philo_ability	new_philo_ability(int argc, char **argv);
t_philo			**create_philos(t_philo_ability ability);
t_fork			**create_forks(int n_philo);
void			create_pthread(t_philo **philos);

long			get_usec();
long			get_elapsed_ms(long start_ms);
void			dying_message(t_philo *philo);
bool			eating(t_philo *philo);
bool			sleeping(t_philo *philo);
bool			thinking(t_philo *philo);
void			print_info(t_philo *philo, char *mes);
bool			check_philo_died(t_philo *philo);
bool			check_philo_ate(int n_philos_ate, int eat_count);

// delete.c
void			delete_forks(t_fork **forks);
void			delete_philos(t_philo **philos);
void			delete_pthread(t_philo **philo);

int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
#endif
