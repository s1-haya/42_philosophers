/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:50:59 by hsawamur          #+#    #+#             */
/*   Updated: 2024/01/16 14:52:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct e_config {
	int		n_philos;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_count;
}	t_config;

typedef struct e_fork {
	pthread_mutex_t	fork;
	int				last_eat_philo;
}	t_fork;

typedef struct e_table {
	bool			is_success;
	bool			is_error;
	bool			is_dead;
	long			start_time;
	int				n_philos_ate;
	t_config		config;
	pthread_mutex_t	print_message;
	pthread_mutex_t	get_data;
}	t_table;

typedef struct e_philo {
	int			id;
	pthread_t	living;
	t_fork		*left;
	t_fork		*right;
	long		last_eat_time;
	int			n_ate;
	t_table		*table;
}	t_philo;

t_table			*new_table(t_config config);
t_philo			*new_philo(size_t id, t_fork *left,
					t_fork *right, t_table *table);
t_fork			*new_fork(void);
t_config		new_config(int argc, char **argv);

t_philo			**create_philos(t_fork **forks, t_table *table);
t_fork			**create_forks(int n_philo);
int				create_pthread(t_philo **philos);

void			*simulation(void *arg);
int				start_simulation(t_philo **philos);

int				get_last_eat_philo_id(t_fork *fork);
bool			get_is_dead(t_table *table);
bool			get_is_success(t_table *table);
bool			get_is_error(t_table *table);
long			get_start_time(t_table *table);

long			get_usec(void);
long			get_elapsed_ms(long start_ms);
void			dying_message(t_philo *philo);
void			perform_eat(t_philo *philo);
void			perform_sleep(t_philo *philo);
void			perform_think(t_philo *philo);
void			print_info(t_philo *philo, char *print_message);
bool			check_philo_died(t_philo *philo);

int				end_simulation(t_philo **philos, int index);
void			delete_philos(t_philo **philos, int index);
void			delete_forks(t_fork **forks);
void			delete_table(t_table *table);

long			ft_strtol(const char *nptr, char **endptr, int base);
size_t			ft_strlen(const char *str);
void			test_usleep(t_philo *philo, long end_time);
#endif
