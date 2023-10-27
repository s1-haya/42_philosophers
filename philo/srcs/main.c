/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:05:39 by hsawamur          #+#    #+#             */
/*   Updated: 2023/10/24 15:51:41 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_error(int argc, char **argv);

#define ERROR_MES_INVALID_ARGUMENT "Invalid argument\n"
#define ERROR_MES_FAILD_INIT "Initialization faild\n"

bool	is_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 4 && argc != 5)
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

// void	exec(t_table *philos)
// {
// 	create_pthread(philos);
// }

int main(int argc, char **argv)
{
	t_philo	**philos;

	philos = set_philos(argc, argv);
	if (philos == NULL)
		return (1);
	create_pthread(philos);
	delete_pthread(philos);
	delete_philos(philos);
	return (0);
}


