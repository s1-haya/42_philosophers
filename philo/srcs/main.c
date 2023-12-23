/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/12/23 15:47:27 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_error(int argc, char **argv);

#define ERROR_MES_INVALID_ARGUMENT "Invalid argument\n"
#define ERROR_MES_FAILD_INIT "Initialization faild\n"

bool	is_error(int argc, char **argv)
{
	(void)argv;
	// printf("argc %d\n", argc);
	if (argc != 5 && argc != 6)
		return (true);
	return (false);
}

t_philo	**set_philos(int argc, char **argv)
{
	t_philo	**philos;

	if (is_error(argc, argv))
	{
		philos = NULL;
		printf(ERROR_MES_INVALID_ARGUMENT);
	}
	else
	{
		philos = create_philos(new_philo_ability(argc, argv));
		if (philos == NULL)
			printf(ERROR_MES_FAILD_INIT);
	}
	return (philos);
}

int main(int argc, char **argv)
{
	t_philo	**philos;

	philos = set_philos(argc, argv);
	if (philos == NULL)
		return (ERROR);
	// create_pthread(philos);
	// wait_for_all_threads_to_finish();
	if (start_simulation(philos) == ERROR)
		return (ERROR);
	return (end_simulation(philos, philos[0]->table->ability.n_philos));
}


