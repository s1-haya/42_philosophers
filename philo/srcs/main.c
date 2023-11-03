/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/11/03 16:29:31 by hsawamur         ###   ########.fr       */
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
	//以下にスコープを減らせるか検討
	t_philo	**philos;

	philos = set_philos(argc, argv);
	if (philos == NULL)
		return (1);
	create_pthread(philos);
	delete_pthread(philos, philos[0]->table->ability.n_philos);
	delete_philos(philos);
	return (0);
}


