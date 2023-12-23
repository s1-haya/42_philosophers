/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:50:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/23 15:52:24 by hsawamur         ###   ########.fr       */
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
# define SUCCESS 1
# define ERROR 0

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
	int				last_eat_philo;
}	t_fork;

typedef struct e_table {
	bool			is_success;
	bool			is_error;
	bool			is_dead;
	long			start_time;
	int				n_philos_ate;
	t_philo_ability	ability;
	pthread_mutex_t	mes;
	pthread_mutex_t	table;
}	t_table;

typedef struct e_philo {
	int				id;
	pthread_t		living;
	struct e_fork	*left;
	struct e_fork	*right;
	long			last_eat_time;
	int				n_ate;
	t_table			*table;
}	t_philo;

// new.c
t_table	*new_table();
t_philo	*new_philo(size_t id, t_fork *left, t_fork *right, t_table *table);
t_fork	*new_fork();

// create.c
t_philo_ability	new_philo_ability(int argc, char **argv);
t_philo			**create_philos(t_philo_ability ability);
t_fork			**create_forks(int n_philo);
int				create_pthread(t_philo **philos);
void			*simulation(void *arg);
int				start_simulation(t_philo **philos);
bool			is_philo_id(int id, t_fork *fork);
int 			read_last_eat_philo_id(t_fork *fork);
bool			read_is_dead(t_table *table);
bool			read_is_success(t_table *table);
bool			read_is_error(t_table *table);
long			read_start_time(t_table *table);
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
int				end_simulation(t_philo **philos, int index);
void			delete_philos(t_philo **philos);
void			delete_forks(t_fork **forks);
void			delete_table(t_table *table);

int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			p_usleep(int end_time);

void	printf_debug_philos(t_philo **philos);
void	printf_debug_table(int id, t_table *table);
#endif
